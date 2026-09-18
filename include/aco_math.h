#ifndef ACO_MATH_H
#define ACO_MATH_H
#include <raylib.h>
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
float dist(Vector2 vec1, Vector2 vec2);
float aco_probablity(float prob1, float dist1, float dist2,
                     float evaporationRate);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !ACO_MATH_H
