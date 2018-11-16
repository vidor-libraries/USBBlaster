#include "Arduino.h"

//#define DEBUG

#ifndef MIN
#define MIN(a,b)    ((a)<=(b)?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b)    ((a)>=(b)?(a):(b))
#endif

#define BITS_SET(v,b)   ((v) |= (b))
#define BITS_CLR(v,b)   ((v) &= ~(b))
#define BITS_CHK(v,b)   (((v) & (b)) == (b))

#define BOOL  bool
#define TRUE  true
#define FALSE false
#define __IO  volatile
#define u32   uint32_t
#define u8    uint8_t

#ifdef DEBUG
#define DEBUG_PRINTLN(...)  Serial1.println(__VA_ARGS__)
#define DEBUG_PRINT(...)    Serial1.print(__VA_ARGS__)
#else
#define DEBUG_PRINTLN(...)
#define DEBUG_PRINT(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif
void led_init(void);
void led_update(void);
void led_light(bool is_light);
void led_flash(uint16_t period, uint16_t pulse, uint16_t cycles);
#ifdef __cplusplus
}
#endif
