#include "../include/aco_math.h"
#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

float *getInitialProbMatrix(int n) {
  float initialProb = (float)1 / (n - 1);
  float *initialProbMatrix = malloc(n * n * sizeof(float));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int idx = getIndex(n, i, j);
      initialProbMatrix[idx] = initialProb * (i != j);
    }
  }
  return initialProbMatrix;
}

int getNextNode(int n, float *probablityArray) {
  float currentProbablity = 0.0;
  float randomFloat = rand() % 100;
  randomFloat /= 100;
  int i = 0;
  for (; i < n; i++) {
    if (probablityArray[i] == 0) {
      continue;
    }
    currentProbablity += probablityArray[i];
    if (randomFloat < currentProbablity) {
      break;
    }
  }
  return i;
}

int *getPath(int n, float *probablityMatrix) {
  int *path = malloc(n * sizeof(int));
  float *probablityArray = malloc(n * sizeof(float));
  for (int i = 0;; i++) {
    if (i == 0) {
      path[i] = rand() % n;
      continue;
    }
    float lastIdx = -1;
    for (int j = 0; j < n; j++) {
      bool isValid = true;
      for (int k = 0; k < i; k++) {
        if (path[k] == j) {
          isValid = false;
        }
      }
      int idx = getIndex(n, path[i - 1], j);
      float probA = probablityMatrix[idx] * isValid;
      if (probA != 0 && i + 1 == n) {
        lastIdx = j;
        break;
      }
      probablityArray[j] = probA;
    }
    if (lastIdx != -1) {
      path[i] = lastIdx;
      break;
    } else {
      do {
        path[i] = getNextNode(n, probablityArray);
      } while (path[i] == n);
    }
  }
  free(probablityArray);
  return path;
}

float getDistance(int n, int *path, float *distanceMatrix) {
  float distance = 0.0;
  for (int i = 0; i < n; i++) {
    int idx = getIndex(n, path[i], path[(i + 1) % n]);
    distance += distanceMatrix[idx];
  }
  return distance;
}

void updateProbablityMatrix(int n, float p, float distance, int *path,
                            float *probablityMatrix) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int idx = getIndex(n, i, j);
      probablityMatrix[idx] *= (1 - p);
    }
  }
  float heauristic = 100 / distance;
  for (int i = 0; i < n; i++) {
    int idx = getIndex(n, path[i], path[(i + 1) % n]);
    probablityMatrix[idx] += heauristic;
  }
  for (int i = 0; i < n; i++) {
    float total = 0.0;
    for (int j = 0; j < n; j++) {
      int idx = getIndex(n, i, j);
      total += probablityMatrix[idx];
    }
    for (int j = 0; j < n; j++) {
      int idx = getIndex(n, i, j);
      probablityMatrix[idx] /= total;
    }
  }
}
