#include "../include/aco_math.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
void DrawHeading() {
  DrawText("ACO", 370, 10, 20, GRAY);
  DrawFPS(10, 10);
}
void DrawNodes(int n, Vector2 *vecArray) {
  for (int i = 0; i < n; i++) {
    DrawCircleV(vecArray[i], 5, GRAY);
  }
}
int main() {
  float thresholdDistance = 25;
  GraphBound bounds = {15, 50, 785, 785};
  int n, l, iter,
      ants; // n: number of nodes; l: number of ants; iter: number of
            // iterations; ants: number of ants currently travelled;
  std::cout << "Enter number of nodes, number of columns: ";
  std::cin >> n >> l;
  std::cout << "Number of nodes: " << n << "\nNumber of ants: " << l << '\n';
  Vector2 *vecArray = getNVector(bounds, n, thresholdDistance);
  float *distanceMatrix = getDistanceMatrix(n, vecArray);
  InitWindow(800, 800, "ACO");
  SetTargetFPS(120);
  ants = 0, iter = 0;
  while (!WindowShouldClose()) {
    ClearBackground(WHITE);
    BeginDrawing();
    DrawHeading();
    DrawNodes(n, vecArray);
    EndDrawing();
  }
  CloseWindow();
  free(vecArray);
  return 0;
}
