#include <nan.h>
#include <v8.h>

#include <iostream>

using namespace v8;


NAN_METHOD(Hello)
{
  info.GetReturnValue().Set(Nan::New("world").ToLocalChecked());
}


NAN_METHOD(Add)
{
  if (info.Length() < 2) {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber())
  {
    Nan::ThrowError("Wrong arguments type");
    return;
  }

  printf("111111111111111\n");
  std::cout << "1234567890" << std::endl;

  double value = info[0]->NumberValue() + info[1]->NumberValue();

  info.GetReturnValue().Set(Nan::New(value));
}

NAN_METHOD(RunCallback)
{
  Local<Function> cb = Local<Function>::Cast(info[1]);
  const unsigned argc = 1;
  Local<Value> argv[argc] = { Nan::New("hello world").ToLocalChecked() };
  cb->Call(Nan::Null(), argc, argv);

  info.GetReturnValue().Set(Nan::New("RunCallback").ToLocalChecked());
  info.GetReturnValue().Set(info[0]);
}

NAN_METHOD(TestType)
{
  int i = 0;
  if (info[i]->IsNumber()) {
    std::cout << "parame " << i << " is number: " << info[i]->NumberValue() << std::endl;
  }

  i++;
  if (info[i]->IsString()) {
    std::string tempString(*Nan::Utf8String(info[i]->ToString()));
    std::cout << "parame " << i << " is string: " << tempString << std::endl;
  }

  i++;
  if (info[i]->IsArray()) {
    std::cout << "parame " << i << " is array: [ ";
    for (int j = 0; j < info[i]->ToObject()->Get(Nan::New("length").ToLocalChecked())->NumberValue(); ++j)
    {
      if (j != 0)
      {
        std::cout << ", ";
      }
      std::string tempString(*Nan::Utf8String(info[i]->ToObject()->Get(j)->ToString()));
      std::cout << tempString;
    }
    std::cout << " ]" << std::endl;
  }

  i++;
  if (info[i]->IsObject()) {
    std::cout << "parame " << i << " is JSON: { ";
    std::string keyString(*Nan::Utf8String((info[i]->ToObject()->GetPropertyNames())->Get(0)->ToString()));
    std::string valString(*Nan::Utf8String(info[i]->ToObject()->Get(Nan::New("hello").ToLocalChecked())));
    std::cout << keyString << ": " << valString;
    std::cout << " }" << std::endl;
  }

  info.GetReturnValue().Set(Nan::New("TestType").ToLocalChecked());
}

NAN_METHOD(ReturnString)
{
  info.GetReturnValue().Set(Nan::New("String").ToLocalChecked());
}

NAN_METHOD(ReturnNumber)
{
  info.GetReturnValue().Set(Nan::New(9999));
}

NAN_METHOD(ReturnArray)
{
  Local<Array> v8Array = Nan::New<Array>();
  v8Array->Set(0, Nan::New("string").ToLocalChecked());
  v8Array->Set(1, Nan::New(1));
  v8Array->Set(2, Nan::New(0.5));

  info.GetReturnValue().Set(v8Array);
}

NAN_METHOD(ReturnJson)
{
  Local<Object> v8Object = Nan::New<Object>();
  v8Object->Set(Nan::New("key").ToLocalChecked(), Nan::New("value").ToLocalChecked());
  v8Object->Set(1, Nan::New("num").ToLocalChecked());

  info.GetReturnValue().Set(v8Object);
}


void init(Handle<Object> exports) {
  Nan::SetMethod(exports, "hello", Hello);
  Nan::SetMethod(exports, "add", Add);
  Nan::SetMethod(exports, "runcb", RunCallback);
  Nan::SetMethod(exports, "testType", TestType);
  Nan::SetMethod(exports, "returnStr", ReturnString);
  Nan::SetMethod(exports, "returnNum", ReturnNumber);
  Nan::SetMethod(exports, "returnArr", ReturnArray);
  Nan::SetMethod(exports, "returnObj", ReturnJson);
}

NODE_MODULE(addon, init)