from __future__ import annotations

from pathlib import Path

from PIL import Image, ImageEnhance


def load_esc190_bin_image(input_path: str) -> Image.Image:
    """Read an ESC190 .bin image: 2 bytes height, 2 bytes width, then RGB data."""
    data = Path(input_path).read_bytes()
    if len(data) < 4:
        raise ValueError("Input file is too small to be a valid ESC190 bin image.")

    height = int.from_bytes(data[0:2], byteorder="big")
    width = int.from_bytes(data[2:4], byteorder="big")
    raster = data[4:]
    expected_size = height * width * 3

    if len(raster) != expected_size:
        raise ValueError(
            f"Invalid raster size: expected {expected_size} bytes, got {len(raster)}."
        )

    return Image.frombytes("RGB", (width, height), raster)


def make_bright_gif(
    input_path: str = "image.bin",
    output_path: str = "brightening.gif",
    frames: int = 12,
    min_brightness: float = 1.0,
    max_brightness: float = 3.0,
    duration_ms: int = 100,
) -> None:
    """Load an ESC190 bin image, generate brighter versions, and save them as a GIF."""
    base = load_esc190_bin_image(input_path)

    generated_frames = []
    for i in range(frames):
        if frames == 1:
            factor = max_brightness
        else:
            factor = min_brightness + (max_brightness - min_brightness) * i / (frames - 1)

        brighter = ImageEnhance.Brightness(base).enhance(factor)
        generated_frames.append(brighter)

    generated_frames[0].save(
        output_path,
        save_all=True,
        append_images=generated_frames[1:],
        duration=duration_ms,
        loop=0,
    )


if __name__ == "__main__":
    make_bright_gif()
