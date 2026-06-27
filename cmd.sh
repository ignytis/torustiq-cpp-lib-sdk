#!/usr/bin/env bash

set -eo pipefail

COMMAND=$1
shift

set -u

if [ "$COMMAND" = "format" ]; then
    find include \( -name '*.cpp' -o -name '*.hpp' \)  | xargs -I % clang-format -i % -style=file
else
    echo "Usage: ./cmd.sh format"
fi