#include "../include/aco_math.h"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>

Vector2 QuadBezier(Vector2 a, Vector2 b, Vector2 c, float t) {
  float u = 1.0f - t;
  Vector2 p;
  p.x = u * u * a.x + 2 * u * t * b.x + t * t * c.x;
  p.y = u * u * a.y + 2 * u * t * b.y + t * t * c.y;
  return p;
}

// Draws n triangles approximating the curve A -> B -> C
void DrawCurveTriangles(Vector2 a, Vector2 b, Vector2 c, int n, Color color) {
  Vector2 prev = QuadBezier(a, b, c, 0.0f); // = a
  for (int i = 1; i <= n; i++) {
    float t = (float)i / (float)n;
    Vector2 curr = QuadBezier(a, b, c, t);
    DrawTriangle(a, prev, curr, color); // fan from a
    prev = curr;
  }
}
void DrawSomething() { DrawCircle(10, 100, 3, GRAY); }
int main() {
  srand(time(0));
  float evaporationRate = 0.2;
  int totalAnts = 100;
  Vector2 arr[4];
  for (int i = 0; i < 4; i++) {
    arr[i].x = rand() % 600 + 150;
    arr[i].y = rand() % 500 + 50;
  }
  float distance[2] = {(dist(arr[0], arr[2])) + (dist(arr[2], arr[1])),
                       (dist(arr[0], arr[3])) + (dist(arr[3], arr[1]))};
  std::cout << "Distance 1: " << distance[0] << " Distance 2: " << distance[1]
            << '\n';
  bool isSmallOne = distance[0] < distance[1];
  float probablity[2] = {0.5, 0.5};
  InitWindow(800, 600, "ACO");
  SetTargetFPS(120);
  int iter = 0;
  int ants = 0;
  int i = 0;
  int antsToOne = 0;
  int antsToTwo = 0;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("ACO", 370, 10, 30, GRAY);
    DrawSomething();
    DrawText(TextFormat("Iteration: %4i", iter), 10, 30, 15, GRAY);
    DrawText(TextFormat("Probablity Route 1: %.4f", probablity[0]), 10, 70, 10,
             GRAY);
    DrawText(TextFormat("Distance Route 1: %.4f", distance[0]), 10, 80, 10,
             GRAY);
    DrawText(TextFormat("Probablity Route 2: %.4f", probablity[1]), 10, 90, 10,
             GRAY);
    DrawText(TextFormat("Distance Route 2: %4f", distance[1]), 10, 100, 10,
             GRAY);
    if (i % 60 < 3) {
      if (i % 30 == 0) {
        ants++;
      }
      if (ants >= totalAnts) {
        ants = 0;
        iter++;
        probablity[0] = aco_probablity(probablity[0], distance[0], distance[1],
                                       evaporationRate);
        probablity[1] = 1 - probablity[0];
        antsToOne = (int)(probablity[0] * totalAnts);
        antsToTwo = (int)(probablity[1] * totalAnts);
        DrawCurveTriangles(arr[0], arr[2], arr[1], antsToOne, RED);
        DrawCurveTriangles(arr[0], arr[3], arr[1], antsToTwo, RED);
      }
      if ((int)(probablity[0] * totalAnts) < ants) {
        // DrawLineV(arr[0], arr[2], RED);
        // DrawLineV(arr[2], arr[1], RED);
      } else {
        // DrawLineV(arr[0], arr[3], RED);
        // DrawLineV(arr[3], arr[1], RED);
      }
    }
    DrawCircleV(arr[0], 10, GRAY);
    DrawText("Nest", arr[0].x - 10, arr[0].y + 10, 15, GRAY);
    DrawCircleV(arr[1], 10, GREEN);
    DrawText("Food", arr[1].x - 10, arr[1].y + 10, 15, GRAY);
    DrawFPS(10, 10);
    EndDrawing();
    i++;
  }
  CloseWindow();
  return 0;
}
