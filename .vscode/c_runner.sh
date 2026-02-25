#!/bin/zsh
set -euo pipefail

mode="${1:-build-run}"
file_name="${2:-}"
file_noext="${3:-}"

mkdir -p build

build_target() {
  if [[ -f main.c ]]; then
    typeset -a sources
    sources=("main.c")

    for f in ./*.c; do
      f="${f#./}"
      [[ "$f" == "main.c" ]] && continue

      base="${f%.c}"
      # Prefer versioned implementations like foo2.c over foo.c when both exist.
      if [[ -f "${base}2.c" ]]; then
        continue
      fi

      sources+=("$f")
    done

    clang -std=c11 -Wall -Wextra -g "${sources[@]}" -o build/main
    return
  fi

  if [[ -z "$file_name" || -z "$file_noext" ]]; then
    echo "Error: file name placeholders were not provided."
    exit 1
  fi

  clang -std=c11 -Wall -Wextra -g "$file_name" -o "build/$file_noext"
}

run_target() {
  if [[ -f main.c ]]; then
    ./build/main
    return
  fi

  if [[ -z "$file_noext" ]]; then
    echo "Error: file basename placeholder was not provided."
    exit 1
  fi

  "./build/$file_noext"
}

case "$mode" in
  build)
    build_target
    ;;
  run)
    run_target
    ;;
  build-run)
    build_target
    run_target
    ;;
  *)
    echo "Usage: c_runner.sh [build|run|build-run] <fileName> <fileNameWithoutExt>"
    exit 1
    ;;
esac
