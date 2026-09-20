#include <raylib.h>

#ifndef ACO_MATH_H
#define ACO_MATH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
typedef struct {
  int lowerX, lowerY, upperX, upperY;
} GraphBound;
int randomInt(int lowerLimit, int upperLimit);
Vector2 randVector(GraphBound bounding);
float dist(Vector2 vec1, Vector2 vec2);
Vector2 *getNVector(GraphBound bounding, int n, float thresholdDistance);
int getIndex(int n, int i, int j);
inline int getIthIndex(int n, int idx);
inline int getJthIndex(int n, int idx);
float *getDistanceMatrix(int n, Vector2 *vecArr);
float *getInitialProbMatrix(int n);
int *getPath(int n, float *probablityMatrix);
float getDistance(int n, int *path, float *distanceMatrix);
void updateProbablityMatrix(int n, float p, float distance, int *path,
                            float *probablityMatrix);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ACO_MATH_H
