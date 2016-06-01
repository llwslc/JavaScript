#include <nan.h>
#include <v8.h>

#include <iostream>
#include <vector>
#include <pthread.h>

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
  if (info[i]->IsNumber()) {
    std::cout << "parame " << i << " is number: " << info[i]->NumberValue() << std::endl;
  }

  i++;
  if (info[i]->IsBoolean()) {
    std::cout << "parame " << i << " is boolean: " << (info[i]->BooleanValue() ? "true" : "false") << std::endl;
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

  i++;
  if (info[i]->IsUndefined()) {
    std::cout << "parame " << i << " is Undefined" << std::endl;
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
  int tempNum = 10000;
  Local<Array> v8Array = Nan::New<Array>();
  v8Array->Set(0, Nan::New("string").ToLocalChecked());
  v8Array->Set(1, Nan::New(1));
  v8Array->Set(2, Nan::New(0.5));

  //-------------------------------------------------------------------
  {
    clock_t _start = clock();
    int count = 512 * 512;
    for (int i = 0; i < count; ++i)
    {
      Local<Array> array = Nan::New<Array>();
    }

    clock_t _end = clock();
    std::cout << "Nan::New<Array>() time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;


    _start = clock();
    for (int i = 0; i < count; ++i)
    {
      Local<Array> array = Nan::New<Array>(10);
    }
    _end = clock();
    std::cout << "Nan::New<Array>(10) time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
  }

  //-------------------------------------------------------------------
  {
    clock_t _start = clock();
    int count = 512 * 512;
    Local<Array> array1 = Nan::New<Array>();
    for (int i = 0; i < count; ++i)
    {
      array1->Set(i, Nan::New<Number>(tempNum));
    }
    clock_t _end = clock();
    std::cout << "Nan::New<Number>(tempNum) time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;

    _start = clock();
    Local<Array> array2 = Nan::New<Array>(count);
    for (int i = 0; i < count; ++i)
    {
      array2->Set(i, Nan::New<Number>(tempNum));
    }
    _end = clock();
    std::cout << "Nan::New<Number>(tempNum) with count time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
  }

  //-------------------------------------------------------------------
  {
    clock_t _start = clock();
    int count = 512 * 512;
    Local<Array> array1 = Nan::New<Array>();
    for (int i = 0; i < count; ++i)
    {
      array1->Set(i, Nan::New<NumberObject>(tempNum));
    }
    clock_t _end = clock();
    std::cout << "Nan::New<NumberObject>(tempNum) time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;

    _start = clock();
    Local<Array> array2 = Nan::New<Array>(count);
    for (int i = 0; i < count; ++i)
    {
      array2->Set(i, Nan::New<NumberObject>(tempNum));
    }
    _end = clock();
    std::cout << "Nan::New<NumberObject>(tempNum) with count time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
  }

  //-------------------------------------------------------------------
  {
    clock_t _start = clock();
    int count = 512 * 512;
    Local<Array> array1 = Nan::New<Array>();
    for (int i = 0; i < count; ++i)
    {
      array1->Set(i, Nan::New(tempNum));
    }
    clock_t _end = clock();
    std::cout << "Nan::New(tempNum) time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;

    _start = clock();
    Local<Array> array2 = Nan::New<Array>(count);
    for (int i = 0; i < count; ++i)
    {
      array2->Set(i, Nan::New(tempNum));
    }
    _end = clock();
    std::cout << "Nan::New(tempNum) with count time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
  }

  //-------------------------------------------------------------------
  {
    clock_t _start = clock();
    int count = 512 * 512;
    int *pArr = new int[count];
    for (int i = 0; i < count; ++i)
    {
      pArr[i] = i;
    }
    clock_t _end = clock();
    std::cout << "new int[count] time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
    delete []pArr;

    _start = clock();
    Local<Array> array2 = Nan::New<Array>(count);
    for (int i = 0; i < count; ++i)
    {
      array2->Set(i, Nan::New(tempNum));
    }
    _end = clock();
    std::cout << "Nan::New(tempNum) with count time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
  }

  //-------------------------------------------------------------------
  {
    int count = 512 * 512;
    int *pArr = new int[count];
    for (int i = 0; i < count; ++i)
    {
      pArr[i] = i;
    }
    clock_t _start = clock();
    int getNum = 0;
    for (int i = 0; i < count; ++i)
    {
      getNum = pArr[i];
    }
    clock_t _end = clock();
    std::cout << "new int[count] loop time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
    delete []pArr;

    Local<Array> array2 = Nan::New<Array>(count);
    for (int i = 0; i < count; ++i)
    {
      array2->Set(i, Nan::New(tempNum));
    }
    _start = clock();
    for (int i = 0; i < count; ++i)
    {
      getNum = array2->Get(i)->NumberValue();
    }
    _end = clock();
    std::cout << "Nan::New(tempNum) with count loop time " << float(_end - _start) / CLOCKS_PER_SEC << " s | count " << count << std::endl;
  }

  info.GetReturnValue().Set(v8Array);
}

NAN_METHOD(ReturnJson)
{
  Local<Array> v8Array = Nan::New<Array>();
  v8Array->Set(0, Nan::New("string").ToLocalChecked());
  v8Array->Set(1, Nan::New(1));
  v8Array->Set(2, Nan::New(0.5));

  Local<Object> v8Object = Nan::New<Object>();
  v8Object->Set(Nan::New("key").ToLocalChecked(), Nan::New("value").ToLocalChecked());
  v8Object->Set(1, Nan::New("num").ToLocalChecked());
  v8Object->Set(Nan::New("arr").ToLocalChecked(), v8Array);

  info.GetReturnValue().Set(v8Object);
}

int myGlobal = 0;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
void *thread_function(void *arg)
{
  int *i = (int*)arg;

  long int wi = 1000;
  while(wi--){ usleep(1); }
  printf("Thread says hi! %d\n", *i);

  pthread_mutex_lock(&myMutex);
  int j = myGlobal;
  j = j + 1;
  myGlobal = j;
  pthread_mutex_unlock(&myMutex);

  return NULL;
}
NAN_METHOD(RunThread)
{
  pthread_t mythread[10] = {};

  for (int i = 0; i < 10; ++i)
  {
    if (pthread_create(&mythread[i], NULL, thread_function, new int(i)))
    {
      printf("error creating thread.");
      abort();
    }
  }

  std::cout << "pthread create over | myGlobal = " << myGlobal << std::endl;

  for (int i = 0; i < 10; ++i)
  {
    if (pthread_join(mythread[i], NULL))
    {
      printf("error joining thread.");
      abort();
    }
  }

  pthread_mutex_lock(&myMutex);
  int j = myGlobal;
  j = j + 1;
  myGlobal = j;
  pthread_mutex_unlock(&myMutex);

  std::cout << "pthread process over | myGlobal = " << myGlobal << std::endl;

  info.GetReturnValue().Set(Nan::New<Object>());
}

NAN_METHOD(ReturnGlobal)
{
  std::cout << "ReturnGlobal = " << myGlobal << std::endl;

  info.GetReturnValue().Set(Nan::New<Object>());
}


void Init(Local<Object> exports) {
  Nan::SetMethod(exports, "hello", Hello);
  Nan::SetMethod(exports, "add", Add);
  Nan::SetMethod(exports, "runcb", RunCallback);
  Nan::SetMethod(exports, "testType", TestType);
  Nan::SetMethod(exports, "returnStr", ReturnString);
  Nan::SetMethod(exports, "returnNum", ReturnNumber);
  Nan::SetMethod(exports, "returnArr", ReturnArray);
  Nan::SetMethod(exports, "returnObj", ReturnJson);
  Nan::SetMethod(exports, "runThread", RunThread);
  Nan::SetMethod(exports, "returnGlobal", ReturnGlobal);
}

NODE_MODULE(addon, Init)