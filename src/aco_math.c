#include "../include/aco_math.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomInt(int lowerLimit, int upperLimit) {
  return (rand() % (upperLimit - lowerLimit) + lowerLimit);
}

Vector2 randVector(GraphBound bounding) {
  Vector2 vec;
  vec.x = randomInt(bounding.lowerX, bounding.upperX);
  vec.y = randomInt(bounding.lowerY, bounding.upperY);
  return vec;
}

float dist(Vector2 vec1, Vector2 vec2) {
  float dx = vec1.x - vec2.x;
  float dy = vec1.y - vec2.y;
  return sqrtf(dx * dx + dy * dy);
}

Vector2 *getNVector(GraphBound bounding, int n, float thresholdDistance) {
  srand(time(0));
  Vector2 *vecArray = malloc(n * sizeof(Vector2));
  for (int i = 0; i < n; i++) {
    bool isValid = true;
    int ntry = 0;
    Vector2 pos;
    do {
      pos = randVector(bounding);
      for (int j = 0; j < i; j++) {
        double distance = dist(pos, vecArray[j]);
        if (distance > thresholdDistance) {
          ntry++;
          isValid = false;
          break;
        }
      }
    } while (!isValid && ntry < 1000);
    vecArray[i] = pos;
  }
  return vecArray;
}

inline int getIndex(int n, int i, int j) { return n * i + j; }
inline int getIthIndex(int n, int idx) { return n / idx; }
inline int getJthIndex(int n, int idx) { return n % idx; }

float *getDistanceMatrix(int n, Vector2 *vecArr) {
  float *distanceMatrix = malloc(n * n * sizeof(float));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int idx = getIndex(n, i, j);
      int invIdx = getIndex(n, j, i);
      float distance = dist(vecArr[i], vecArr[j]);
      distanceMatrix[idx] = distance;
      distanceMatrix[invIdx] = distance;
    }
  }
  return distanceMatrix;
}
