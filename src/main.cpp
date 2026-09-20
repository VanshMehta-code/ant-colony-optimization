#include "../include/aco_math.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
void DrawHeading(int iter, int ants, float bestDistance, float distance) {
  DrawText("ACO", 370, 10, 25, GRAY);
  DrawText(TextFormat("Iteration: %4i", iter), 10, 32, 15, GRAY);
  DrawText(TextFormat("Ants: %4i", ants), 10, 47, 15, GRAY);
  DrawText(TextFormat("Best Distance: %4f", bestDistance), 10, 63, 15, GRAY);
  DrawText(TextFormat("Current Distance: %4f", distance), 10, 78, 15, GRAY);
  DrawFPS(10, 10);
}
void DrawEdges(int n, Vector2 *vecArray) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      DrawLineV(vecArray[i], vecArray[j], GRAY);
    }
  }
}
void DrawNodes(int n, Vector2 *vecArray) {
  for (int i = 0; i < n; i++) {
    DrawCircleV(vecArray[i], 5, GRAY);
  }
}
void DrawPath(Vector2 startPos, Vector2 endPos) {
  DrawLineV(startPos, endPos, RED);
}
void DrawBestPath(int n, int *path, Vector2 *vecArray) {
  for (int i = 0; i < n; i++) {
    DrawLineV(vecArray[path[i]], vecArray[path[(i + 1) % n]], GRAY);
  }
}
void DrawHostNode(Vector2 host) { DrawCircleV(host, 5, RED); }
int main() {
  srand(time(0));
  float thresholdDistance = 30;
  float p = 0.2;
  GraphBound bounds = {15, 100, 785, 785};
  int n = 0, l = 0, iter = 0, ants = 1, frame = 0,
      idx = 0; // n: number of nodes; l: number of ants; iter: number of
               // iterations; ants: number of ants currently travelled;
  std::cout << "Enter number of nodes, number of ants: ";
  std::cin >> n >> l;
  Vector2 *vecArray = getNVector(bounds, n, thresholdDistance);
  float *distanceMatrix = getDistanceMatrix(n, vecArray);
  float *probablityMatrix = getInitialProbMatrix(n);
  int *path = getPath(n, probablityMatrix);
  int *bestPath = path;
  float distance = 0;
  float bestDistance = 0;
  bool isRepeated = true;
  InitWindow(800, 800, "ACO");
  SetTargetFPS(120);
  while (!WindowShouldClose()) {
    if (++frame >= 6) {
      frame = 0;
      idx = (idx + 1) % n;
      if (idx == 0 && isRepeated) {
        isRepeated = !isRepeated;
        distance = getDistance(n, path, distanceMatrix);
        if (distance < bestDistance || bestDistance == 0) {
          bestPath = path;
          bestDistance = distance;
        }
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            int idx = getIndex(n, i, j);
            std::cout << probablityMatrix[idx] << ", ";
          }
          std::cout << '\n';
        }
        updateProbablityMatrix(n, p, distance, path, probablityMatrix);
        if (++ants >= l) {
          ants = 0;
          iter++;
        }
        path = getPath(n, probablityMatrix);
      }
    }
    if (idx == 0 && !isRepeated) {
      isRepeated = !isRepeated;
      frame = 0;
      idx = 0;
    }
    ClearBackground(WHITE);
    BeginDrawing();
    DrawHeading(iter, ants, bestDistance, distance);
    // DrawEdges(n, vecArray);
    DrawBestPath(n, bestPath, vecArray);
    DrawPath(vecArray[path[idx]], vecArray[path[(idx + 1) % n]]);
    DrawNodes(n, vecArray);
    DrawHostNode(vecArray[path[idx]]);
    EndDrawing();
  }
  CloseWindow();
  free(vecArray);
  free(distanceMatrix);
  free(probablityMatrix);
  free(path);
  return 0;
}
