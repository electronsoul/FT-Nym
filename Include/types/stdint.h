#ifndef STDINT_H
#define STDINT_H

#if defined __C51__

//typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
//typedef unsigned long uint32_t;
//typedef uint32_t uint64_t[2];

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;
typedef int32_t int64_t[2];

#endif

#endif