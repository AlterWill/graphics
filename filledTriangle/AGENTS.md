# AGENTS.md

## File edit permissions

You may only edit `src/main.cpp`. Do not create, modify, delete, move or rename any
other file in this repository.

Files that are **off limits** (read them, but never write to them):

- `include/frame.hpp` — the software rasterizer (vertex positions, line drawing)
- `include/image.hpp` — the framebuffer
- `include/colour.hpp` — pixel colour packing
- `include/point.hpp` — the vertex type
- `CMakeLists.txt` — build configuration
- `AGENTS.md` — this file

If a fix requires changing one of those files, **stop and tell the user what needs to
change and why**. Do not apply the change yourself, and do not work around it by
editing an off-limits file indirectly (for example by redefining a header's contents
from `main.cpp`).

## `src/main.cpp` scope

`src/main.cpp` contains SDL code only. It owns the SDL lifecycle and nothing else:

- `SDL_Init` / `SDL_Quit`
- `SDL_CreateWindow` / `SDL_CreateRenderer` / `SDL_CreateTexture`
- `SDL_UpdateTexture`, `SDL_RenderClear`, `SDL_RenderTexture`, `SDL_RenderPresent`
- the `SDL_Event` poll loop and teardown calls
- printing SDL errors with `SDL_GetError`

It must **not** contain any rendering logic of its own. Specifically, no geometry,
line rasterization, vertex positions, shading or per-pixel math. All drawing decisions
belong to `Frame` in `include/frame.hpp`; this file only uploads the finished
`Image` and presents it.

## Constraints to preserve in `src/main.cpp`

- The texture format must stay `SDL_PIXELFORMAT_ABGR8888`.
- `Colour` packs a pixel as `AABBGGRR`, so on little-endian the bytes in memory are
  `R, G, B, A`. SDL3 aliases `SDL_PIXELFORMAT_RGBA32` to `SDL_PIXELFORMAT_ABGR8888`
  on little-endian (see `SDL_pixels.h`), and `ABGR8888` is the name that matches the
  `AABBGGRR` bit layout literally. **Do not "simplify" this to `RRGGBBAA`.** Doing so
  puts the alpha value in the red byte and renders green and blue with alpha 0, i.e.
  invisible. This is the reason the triangle used to vanish.
- The `SDL_UpdateTexture` pitch is `image.getWidth() * sizeof(uint32_t)`.

## Rendering model, for context

`Image` is a row-major `uint32_t` framebuffer indexed as `y * width + x`, with `y = 0`
at the top. `Image::setPixel` silently discards writes outside the image bounds, so a
coordinate out of range fails quietly with no error or crash. A blank screen is
therefore usually one of: an out-of-bounds coordinate, an invisible alpha channel, or a
draw loop that never executes.
