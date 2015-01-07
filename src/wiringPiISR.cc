#include "wiringPiISR.h"
#include <wiringPi.h>
#include <iostream>
#include <map>
#include <uv.h>

using namespace v8;

typedef struct js_work_t {
    uv_work_t req;
    int pin;
    unsigned int delta;
} js_work_t;

typedef void (*NATIVE_INTERRUPT_HANDLER_T)(void);

static NATIVE_INTERRUPT_HANDLER_T nativeInterruptHandlers[64];
static unsigned long int lastInterruptMicroseconds[64];
static std::map<int, Persistent<Function> > interruptCallbackMapping;

#define DEFINE_NATIVE_INTERRUPT_HANDLER(pin) \
    static void nativeInterruptHandler##pin(void) { \
        processNativeInterrupt(pin); \
    }
    
#define REGISTER_NATIVE_INTERRUPT_HANDLER(pin) nativeInterruptHandlers[pin] = &nativeInterruptHandler##pin

#define GET_NATIVE_INTERRUPT_HANDLER(pin) nativeInterruptHandlers[pin]

static void processInterrupt(uv_work_t* req, int status) {
    js_work_t* work = static_cast<js_work_t*>(req->data);
    
    Persistent<Function> callback = interruptCallbackMapping[work->pin];
    
    Local<Value> argv[] = {
      Local<Value>::New(Uint32::New(work->delta))
    };
    
    callback->Call(Context::GetCurrent()->Global(), 1, argv);
    
    delete work;
}

static void UV_NOP(uv_work_t*) {}

void processNativeInterrupt(int pin) {
    unsigned int now = ::micros();
    
    js_work_t* work = new js_work_t;
    work->req.data = work;
    work->pin = pin;
    work->delta = now - lastInterruptMicroseconds[pin];
     
    int r = uv_queue_work(uv_default_loop(), &work->req, &UV_NOP, &processInterrupt);
    if (r != 0) {
        delete work;
    }
    
    lastInterruptMicroseconds[pin] = now;
}

DEFINE_NATIVE_INTERRUPT_HANDLER(0);
DEFINE_NATIVE_INTERRUPT_HANDLER(1);
DEFINE_NATIVE_INTERRUPT_HANDLER(2);
DEFINE_NATIVE_INTERRUPT_HANDLER(3);
DEFINE_NATIVE_INTERRUPT_HANDLER(4);
DEFINE_NATIVE_INTERRUPT_HANDLER(5);
DEFINE_NATIVE_INTERRUPT_HANDLER(6);
DEFINE_NATIVE_INTERRUPT_HANDLER(7);
DEFINE_NATIVE_INTERRUPT_HANDLER(8);
DEFINE_NATIVE_INTERRUPT_HANDLER(9);
DEFINE_NATIVE_INTERRUPT_HANDLER(10);
DEFINE_NATIVE_INTERRUPT_HANDLER(11);
DEFINE_NATIVE_INTERRUPT_HANDLER(12);
DEFINE_NATIVE_INTERRUPT_HANDLER(13);
DEFINE_NATIVE_INTERRUPT_HANDLER(14);
DEFINE_NATIVE_INTERRUPT_HANDLER(15);
DEFINE_NATIVE_INTERRUPT_HANDLER(16);
DEFINE_NATIVE_INTERRUPT_HANDLER(17);
DEFINE_NATIVE_INTERRUPT_HANDLER(18);
DEFINE_NATIVE_INTERRUPT_HANDLER(19);
DEFINE_NATIVE_INTERRUPT_HANDLER(20);
DEFINE_NATIVE_INTERRUPT_HANDLER(21);
DEFINE_NATIVE_INTERRUPT_HANDLER(22);
DEFINE_NATIVE_INTERRUPT_HANDLER(23);
DEFINE_NATIVE_INTERRUPT_HANDLER(24);
DEFINE_NATIVE_INTERRUPT_HANDLER(25);
DEFINE_NATIVE_INTERRUPT_HANDLER(26);
DEFINE_NATIVE_INTERRUPT_HANDLER(27);
DEFINE_NATIVE_INTERRUPT_HANDLER(28);
DEFINE_NATIVE_INTERRUPT_HANDLER(29);
DEFINE_NATIVE_INTERRUPT_HANDLER(30);
DEFINE_NATIVE_INTERRUPT_HANDLER(31);
DEFINE_NATIVE_INTERRUPT_HANDLER(32);
DEFINE_NATIVE_INTERRUPT_HANDLER(33);
DEFINE_NATIVE_INTERRUPT_HANDLER(34);
DEFINE_NATIVE_INTERRUPT_HANDLER(35);
DEFINE_NATIVE_INTERRUPT_HANDLER(36);
DEFINE_NATIVE_INTERRUPT_HANDLER(37);
DEFINE_NATIVE_INTERRUPT_HANDLER(38);
DEFINE_NATIVE_INTERRUPT_HANDLER(39);
DEFINE_NATIVE_INTERRUPT_HANDLER(40);
DEFINE_NATIVE_INTERRUPT_HANDLER(41);
DEFINE_NATIVE_INTERRUPT_HANDLER(42);
DEFINE_NATIVE_INTERRUPT_HANDLER(43);
DEFINE_NATIVE_INTERRUPT_HANDLER(44);
DEFINE_NATIVE_INTERRUPT_HANDLER(45);
DEFINE_NATIVE_INTERRUPT_HANDLER(46);
DEFINE_NATIVE_INTERRUPT_HANDLER(47);
DEFINE_NATIVE_INTERRUPT_HANDLER(48);
DEFINE_NATIVE_INTERRUPT_HANDLER(49);
DEFINE_NATIVE_INTERRUPT_HANDLER(50);
DEFINE_NATIVE_INTERRUPT_HANDLER(51);
DEFINE_NATIVE_INTERRUPT_HANDLER(52);
DEFINE_NATIVE_INTERRUPT_HANDLER(53);
DEFINE_NATIVE_INTERRUPT_HANDLER(54);
DEFINE_NATIVE_INTERRUPT_HANDLER(55);
DEFINE_NATIVE_INTERRUPT_HANDLER(56);
DEFINE_NATIVE_INTERRUPT_HANDLER(57);
DEFINE_NATIVE_INTERRUPT_HANDLER(58);
DEFINE_NATIVE_INTERRUPT_HANDLER(59);
DEFINE_NATIVE_INTERRUPT_HANDLER(60);
DEFINE_NATIVE_INTERRUPT_HANDLER(61);
DEFINE_NATIVE_INTERRUPT_HANDLER(62);
DEFINE_NATIVE_INTERRUPT_HANDLER(63);

DECLARE(wiringPiISR);
IMPLEMENT(wiringPiISR) {
  SCOPE_OPEN();
  
  SET_ARGUMENT_NAME(0, pin);
  SET_ARGUMENT_NAME(1, edgeType);
  SET_ARGUMENT_NAME(2, callback);
  
  CHECK_ARGUMENTS_LENGTH_EQUAL(3);
  
  CHECK_ARGUMENT_TYPE_INT32(0);
  CHECK_ARGUMENT_TYPE_INT32(1);
  CHECK_ARGUMENT_TYPE_FUNCTION(2);
  
  int pin = GET_ARGUMENT_AS_INT32(0);
  int edgeType = GET_ARGUMENT_AS_INT32(1);
  Persistent<Function> callback = GET_ARGUMENT_AS_PERSISTENT_FUNCTION(2);
  
  CHECK_ARGUMENT_IN_INTS(1, edgeType, (INT_EDGE_FALLING, INT_EDGE_RISING, INT_EDGE_BOTH, INT_EDGE_SETUP));
  
  interruptCallbackMapping.insert(std::pair<int, Persistent<Function> >(pin, callback));
  lastInterruptMicroseconds[pin] = ::micros();
  
  ::wiringPiISR(pin, edgeType, GET_NATIVE_INTERRUPT_HANDLER(pin));
  
  SCOPE_CLOSE(UNDEFINED());
}

IMPLEMENT_EXPORT_INIT(wiringPiISR) {
    REGISTER_NATIVE_INTERRUPT_HANDLER(0);
    REGISTER_NATIVE_INTERRUPT_HANDLER(1);
    REGISTER_NATIVE_INTERRUPT_HANDLER(2);
    REGISTER_NATIVE_INTERRUPT_HANDLER(3);
    REGISTER_NATIVE_INTERRUPT_HANDLER(4);
    REGISTER_NATIVE_INTERRUPT_HANDLER(5);
    REGISTER_NATIVE_INTERRUPT_HANDLER(6);
    REGISTER_NATIVE_INTERRUPT_HANDLER(7);
    REGISTER_NATIVE_INTERRUPT_HANDLER(8);
    REGISTER_NATIVE_INTERRUPT_HANDLER(9);
    REGISTER_NATIVE_INTERRUPT_HANDLER(10);
    REGISTER_NATIVE_INTERRUPT_HANDLER(11);
    REGISTER_NATIVE_INTERRUPT_HANDLER(12);
    REGISTER_NATIVE_INTERRUPT_HANDLER(13);
    REGISTER_NATIVE_INTERRUPT_HANDLER(14);
    REGISTER_NATIVE_INTERRUPT_HANDLER(15);
    REGISTER_NATIVE_INTERRUPT_HANDLER(16);
    REGISTER_NATIVE_INTERRUPT_HANDLER(17);
    REGISTER_NATIVE_INTERRUPT_HANDLER(18);
    REGISTER_NATIVE_INTERRUPT_HANDLER(19);
    REGISTER_NATIVE_INTERRUPT_HANDLER(20);
    REGISTER_NATIVE_INTERRUPT_HANDLER(21);
    REGISTER_NATIVE_INTERRUPT_HANDLER(22);
    REGISTER_NATIVE_INTERRUPT_HANDLER(23);
    REGISTER_NATIVE_INTERRUPT_HANDLER(24);
    REGISTER_NATIVE_INTERRUPT_HANDLER(25);
    REGISTER_NATIVE_INTERRUPT_HANDLER(26);
    REGISTER_NATIVE_INTERRUPT_HANDLER(27);
    REGISTER_NATIVE_INTERRUPT_HANDLER(28);
    REGISTER_NATIVE_INTERRUPT_HANDLER(29);
    REGISTER_NATIVE_INTERRUPT_HANDLER(30);
    REGISTER_NATIVE_INTERRUPT_HANDLER(31);
    REGISTER_NATIVE_INTERRUPT_HANDLER(32);
    REGISTER_NATIVE_INTERRUPT_HANDLER(33);
    REGISTER_NATIVE_INTERRUPT_HANDLER(34);
    REGISTER_NATIVE_INTERRUPT_HANDLER(35);
    REGISTER_NATIVE_INTERRUPT_HANDLER(36);
    REGISTER_NATIVE_INTERRUPT_HANDLER(37);
    REGISTER_NATIVE_INTERRUPT_HANDLER(38);
    REGISTER_NATIVE_INTERRUPT_HANDLER(39);
    REGISTER_NATIVE_INTERRUPT_HANDLER(40);
    REGISTER_NATIVE_INTERRUPT_HANDLER(41);
    REGISTER_NATIVE_INTERRUPT_HANDLER(42);
    REGISTER_NATIVE_INTERRUPT_HANDLER(43);
    REGISTER_NATIVE_INTERRUPT_HANDLER(44);
    REGISTER_NATIVE_INTERRUPT_HANDLER(45);
    REGISTER_NATIVE_INTERRUPT_HANDLER(46);
    REGISTER_NATIVE_INTERRUPT_HANDLER(47);
    REGISTER_NATIVE_INTERRUPT_HANDLER(48);
    REGISTER_NATIVE_INTERRUPT_HANDLER(49);
    REGISTER_NATIVE_INTERRUPT_HANDLER(50);
    REGISTER_NATIVE_INTERRUPT_HANDLER(51);
    REGISTER_NATIVE_INTERRUPT_HANDLER(52);
    REGISTER_NATIVE_INTERRUPT_HANDLER(53);
    REGISTER_NATIVE_INTERRUPT_HANDLER(54);
    REGISTER_NATIVE_INTERRUPT_HANDLER(55);
    REGISTER_NATIVE_INTERRUPT_HANDLER(56);
    REGISTER_NATIVE_INTERRUPT_HANDLER(57);
    REGISTER_NATIVE_INTERRUPT_HANDLER(58);
    REGISTER_NATIVE_INTERRUPT_HANDLER(59);
    REGISTER_NATIVE_INTERRUPT_HANDLER(60);
    REGISTER_NATIVE_INTERRUPT_HANDLER(61);
    REGISTER_NATIVE_INTERRUPT_HANDLER(62);
    REGISTER_NATIVE_INTERRUPT_HANDLER(63);
    
    EXPORT_FUNCTION(wiringPiISR);
    
    EXPORT_CONSTANT_INT(INT_EDGE_FALLING);
    EXPORT_CONSTANT_INT(INT_EDGE_RISING);
    EXPORT_CONSTANT_INT(INT_EDGE_BOTH);
    EXPORT_CONSTANT_INT(INT_EDGE_SETUP);
}