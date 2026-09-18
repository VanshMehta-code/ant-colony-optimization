#include "../include/aco_math.h"
#include <math.h>
#include <raylib.h>
float dist(Vector2 vec1, Vector2 vec2) {
  float dx = vec1.x - vec2.x;
  float dy = vec1.y - vec2.y;
  float distance = sqrtf(dx * dx + dy * dy);
  return distance;
}
float aco_probablity(float prob1, float dist1, float dist2,
                     float evaporationRate) {
  float prob2 = 1 - prob1;
  float heauristic1 = 1 / dist1;
  float heauristic2 = 1 / dist2;
  prob1 += heauristic1;
  prob2 += heauristic2;
  prob1 *= (1 - evaporationRate);
  prob2 *= (1 - evaporationRate);
  float totalposs = prob1 + prob2;
  prob1 = prob1 / totalposs;
  prob2 = prob2 / totalposs;
  return prob1;
}
