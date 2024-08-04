// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "maluuba/speech/nodejs/stringdistance.hpp"
#include <string>
#include <utility>

namespace maluuba
{
namespace speech
{
namespace nodejs
{
  v8::Persistent<v8::Function> StringDistance::s_constructor;
  v8::Persistent<v8::FunctionTemplate> StringDistance::s_type;

  StringDistance::StringDistance(LevenshteinDistance<> distance)
    : m_distance{std::move(distance)}
  { }

  StringDistance::~StringDistance() = default;

  v8::Local<v8::FunctionTemplate>
  StringDistance::type(v8::Isolate* isolate)
  {
    return s_type.Get(isolate);
  }

  void
  StringDistance::Init(v8::Local<v8::Object> exports)
  {
    auto isolate = exports->GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    auto tpl = v8::FunctionTemplate::New(isolate, New);
    tpl->SetClassName(v8::String::NewFromUtf8(isolate, "StringDistance").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "distance", Distance);

    auto maybe_function = tpl->GetFunction(context);
    if (maybe_function.IsEmpty()) {
      // Handle error
      return;
    }
    s_constructor.Reset(isolate, maybe_function.ToLocalChecked());
    s_type.Reset(isolate, tpl);
    
    v8::Local<v8::String> exportName = v8::String::NewFromUtf8(isolate, "StringDistance").ToLocalChecked();
    exports->Set(context, exportName, maybe_function.ToLocalChecked()).Check();
  }

  void
  StringDistance::New(const v8::FunctionCallbackInfo<v8::Value>& args)
  {
    auto isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
      LevenshteinDistance<> distance{};
      auto obj = new StringDistance(std::move(distance));
      obj->Wrap(args.This());
      args.GetReturnValue().Set(args.This());
    } else {
      isolate->ThrowException(v8::Exception::SyntaxError(
        v8::String::NewFromUtf8(isolate, "Not invoked as constructor, change to: `new StringDistance()`").ToLocalChecked()));
      return;
    }
  }

  void
  StringDistance::Distance(const v8::FunctionCallbackInfo<v8::Value>& args)
  {
    auto isolate = args.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    if (args.Length() < 2) {
      isolate->ThrowException(v8::Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Expected 2 arguments.").ToLocalChecked()));
      return;
    }

    if (!args[0]->IsString() || !args[1]->IsString()) {
      isolate->ThrowException(v8::Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Expected arguments to be string.").ToLocalChecked()));
      return;
    }

    auto obj = ObjectWrap::Unwrap<StringDistance>(args.Holder());
    v8::String::Utf8Value a_utf8(isolate, args[0]);
    v8::String::Utf8Value b_utf8(isolate, args[1]);
    std::string a(*a_utf8);
    std::string b(*b_utf8);
    auto distance = obj->distance()(a, b);

    args.GetReturnValue().Set(v8::Number::New(isolate, distance));
  }

  const LevenshteinDistance<>&
  StringDistance::distance() const
  {
    return m_distance;
  }
}
}
}