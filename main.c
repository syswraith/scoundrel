#include "raylib.h"
#include "cards.h"

typedef struct PlayerStats {
  int health;

} PlayerStats_t;

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  PlayerStats_t stats = {
    .health = 20,
  };

  InitWindow(screenWidth, screenHeight, "scoundrel");

  Image image = LoadImage(CLUBS_1);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
    DrawTexture(
      texture, 
      screenWidth / 2 - texture.width / 2,
      screenHeight / 2 - texture.height / 2, 
      WHITE
    );

    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
