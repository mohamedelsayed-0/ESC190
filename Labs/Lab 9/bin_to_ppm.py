from __future__ import annotations

import argparse
from pathlib import Path


def read_esc190_bin(path: Path) -> tuple[int, int, bytes]:
    data = path.read_bytes()
    if len(data) < 4:
        raise ValueError(f"{path} is too small to be a valid ESC190 .bin image.")

    height = int.from_bytes(data[0:2], byteorder="big")
    width = int.from_bytes(data[2:4], byteorder="big")
    raster = data[4:]
    expected_size = height * width * 3

    if len(raster) != expected_size:
        raise ValueError(
            f"{path} has invalid raster size: expected {expected_size} bytes, got {len(raster)}."
        )

    return height, width, raster


def write_ppm(path: Path, width: int, height: int, raster: bytes) -> None:
    header = f"P6\n{width} {height}\n255\n".encode("ascii")
    path.write_bytes(header + raster)


def convert_file(input_path: Path, output_dir: Path | None) -> Path:
    height, width, raster = read_esc190_bin(input_path)
    output_path = (
        (output_dir / f"{input_path.stem}.ppm") if output_dir else input_path.with_suffix(".ppm")
    )
    write_ppm(output_path, width, height, raster)
    return output_path


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Convert ESC190 .bin images into .ppm files that standard image viewers can open."
    )
    parser.add_argument("inputs", nargs="+", help="One or more ESC190 .bin image files")
    parser.add_argument(
        "--out-dir",
        type=Path,
        help="Optional output directory for generated .ppm files",
    )
    args = parser.parse_args()

    if args.out_dir is not None:
        args.out_dir.mkdir(parents=True, exist_ok=True)

    for input_name in args.inputs:
        input_path = Path(input_name)
        output_path = convert_file(input_path, args.out_dir)
        print(f"{input_path} -> {output_path}")


if __name__ == "__main__":
    main()
