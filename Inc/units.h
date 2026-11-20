#ifndef UNITS_H_
#define UNITS_H_

#define HZ_PER_KHZ 1000U
#define HZ_PER_MHZ 1000000U
#define MS_PER_S 1000U
#define PERCENT_MAX 100U

#define BITS_PER_BYTE 8U
#define BYTE_MASK 0xFFU

#define DIV_ROUND(n, d) (((n) + ((d) / 2U)) / (d))

#endif // UNITS_H_