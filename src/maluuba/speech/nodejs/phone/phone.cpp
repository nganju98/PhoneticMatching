// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "maluuba/speech/nodejs/phone.hpp"
#include <utility>

namespace maluuba
{
namespace speech
{
namespace nodejs
{
  namespace
  {
    void
    getType(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      auto type = static_cast<uint32_t>(obj->phone().type());
      info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, type));
    }

    void
    getPhonation(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      auto phonation = static_cast<uint32_t>(obj->phone().phonation());
      info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, phonation));
    }

    void
    getPlace(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      // consonant
      try {
        auto place = static_cast<uint32_t>(obj->phone().place());
        info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, place));
      } catch (const std::exception& e) {
        info.GetReturnValue().Set(v8::Undefined(isolate));
      }
    }

    void
    getManner(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      // consonant
      try {
        auto manner = static_cast<uint32_t>(obj->phone().manner());
        info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, manner));
      } catch (const std::exception& e) {
        info.GetReturnValue().Set(v8::Undefined(isolate));
      }
    }

    void
    getHeight(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      // vowel
      try {
        auto height = static_cast<uint32_t>(obj->phone().height());
        info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, height));
      } catch (const std::exception& e) {
        info.GetReturnValue().Set(v8::Undefined(isolate));
      }
    }

    void
    getBackness(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      // vowel
      try {
        auto backness = static_cast<uint32_t>(obj->phone().backness());
        info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, backness));
      } catch (const std::exception& e) {
        info.GetReturnValue().Set(v8::Undefined(isolate));
      }
    }

    void
    getRoundedness(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      // vowel
      try {
        auto roundedness = static_cast<uint32_t>(obj->phone().roundedness());
        info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, roundedness));
      } catch (const std::exception& e) {
        info.GetReturnValue().Set(v8::Undefined(isolate));
      }
    }

    void
    getRhotic(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      // vowel
      try {
        auto rhotic = obj->phone().is_rhotic();
        info.GetReturnValue().Set(v8::Boolean::New(isolate, rhotic));
      } catch (const std::exception& e) {
        info.GetReturnValue().Set(v8::Undefined(isolate));
      }
    }

    void
    getSyllabic(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
      auto isolate = info.GetIsolate();
      auto obj = node::ObjectWrap::Unwrap<nodejs::Phone>(info.Holder());
      auto syllabic = obj->phone().is_syllabic();
      info.GetReturnValue().Set(v8::Boolean::New(isolate, syllabic));
    }

    void
    setThrow(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
    {
      auto isolate = info.GetIsolate();
      isolate->ThrowException(v8::Exception::Error(
          v8::String::NewFromUtf8(isolate, "Object is immutable, setters not allowed.").ToLocalChecked()));
      return;
    }
  }

  v8::Persistent<v8::Function> Phone::s_constructor;

  Phone::Phone(speech::Phone phone)
    : m_phone{std::move(phone)}
  { }

  v8::Local<v8::Function>
  Phone::constructor(v8::Isolate* isolate)
  {
    return v8::Local<v8::Function>::New(isolate, s_constructor);
  }

  void
  Phone::Init(v8::Local<v8::Object> exports)
  {
    auto isolate = exports->GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    auto tpl = v8::FunctionTemplate::New(isolate, New);
    tpl->SetClassName(v8::String::NewFromUtf8(isolate, "Phone").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Create local strings for all property names
    v8::Local<v8::String> typeStr = v8::String::NewFromUtf8(isolate, "type").ToLocalChecked();
    v8::Local<v8::String> phonationStr = v8::String::NewFromUtf8(isolate, "phonation").ToLocalChecked();
    v8::Local<v8::String> placeStr = v8::String::NewFromUtf8(isolate, "place").ToLocalChecked();
    v8::Local<v8::String> mannerStr = v8::String::NewFromUtf8(isolate, "manner").ToLocalChecked();
    v8::Local<v8::String> heightStr = v8::String::NewFromUtf8(isolate, "height").ToLocalChecked();
    v8::Local<v8::String> backnessStr = v8::String::NewFromUtf8(isolate, "backness").ToLocalChecked();
    v8::Local<v8::String> roundednessStr = v8::String::NewFromUtf8(isolate, "roundedness").ToLocalChecked();
    v8::Local<v8::String> isRhoticStr = v8::String::NewFromUtf8(isolate, "isRhotic").ToLocalChecked();
    v8::Local<v8::String> isSyllabicStr = v8::String::NewFromUtf8(isolate, "isSyllabic").ToLocalChecked();

    // Set accessors using the local strings
    tpl->InstanceTemplate()->SetAccessor(typeStr, getType, setThrow);
    tpl->InstanceTemplate()->SetAccessor(phonationStr, getPhonation, setThrow);
    tpl->InstanceTemplate()->SetAccessor(placeStr, getPlace, setThrow);
    tpl->InstanceTemplate()->SetAccessor(mannerStr, getManner, setThrow);
    tpl->InstanceTemplate()->SetAccessor(heightStr, getHeight, setThrow);
    tpl->InstanceTemplate()->SetAccessor(backnessStr, getBackness, setThrow);
    tpl->InstanceTemplate()->SetAccessor(roundednessStr, getRoundedness, setThrow);
    tpl->InstanceTemplate()->SetAccessor(isRhoticStr, getRhotic, setThrow);
    tpl->InstanceTemplate()->SetAccessor(isSyllabicStr, getSyllabic, setThrow);

    auto maybe_function = tpl->GetFunction(context);
    if (maybe_function.IsEmpty()) {
      // Handle error
      return;
    }
    s_constructor.Reset(isolate, maybe_function.ToLocalChecked());
  }

  void
  Phone::New(const v8::FunctionCallbackInfo<v8::Value>& args)
  {
    auto isolate = args.GetIsolate();

    if (!args[0]->IsExternal()) {
      isolate->ThrowException(v8::Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Not Expected to initialize directly, use EnPronunciation.").ToLocalChecked()));
      return;
    }

    auto self = args.Holder();
    auto external = args[0].As<v8::External>();
    auto obj = static_cast<Phone*>(external->Value());
    obj->Wrap(self);
    args.GetReturnValue().Set(self);
  }

  const speech::Phone&
  Phone::phone() const
  {
    return m_phone;
  }
}
}
}