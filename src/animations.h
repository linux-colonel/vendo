#pragma once

typedef struct animation {
  const char* name;
  unsigned (*animation)(bool init);
  bool ignores_presets;
} animation_t;

extern animation_t animations[];
extern unsigned animations_length;

extern animation_t* current_animation;

animation_t* animation_lookup(const char*);
void animation_set(animation_t*);
bool animation_set(const char*);
void animation_speed(float);
float animation_speed(void);
void animation_start();
void animation_stop();
unsigned animate();
