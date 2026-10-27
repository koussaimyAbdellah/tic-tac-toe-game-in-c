#!/usr/bin/env bash
set -eu

APP_DIR="$HOME/.local/opt/tic-tac-toe"
ICON_FILE="$HOME/.local/share/icons/tic-tac-toe.svg"
MENU_FILE="$HOME/.local/share/applications/tic-tac-toe.desktop"
DESKTOP_DIR="$(xdg-user-dir DESKTOP 2>/dev/null || true)"
DESKTOP_FILE=""

if [ -n "$DESKTOP_DIR" ] && [ -d "$DESKTOP_DIR" ]; then
    DESKTOP_FILE="$DESKTOP_DIR/tic-tac-toe.desktop"
fi

if [ -f "$MENU_FILE" ] && grep -Fq "Exec=$APP_DIR/tic-tac-toe" "$MENU_FILE"; then
    rm -f -- "$MENU_FILE"
    echo "Removed application-menu launcher."
fi

if [ -n "$DESKTOP_FILE" ] && [ -f "$DESKTOP_FILE" ] && \
   grep -Fq "Exec=$APP_DIR/tic-tac-toe" "$DESKTOP_FILE"; then
    rm -f -- "$DESKTOP_FILE"
    echo "Removed desktop shortcut."
fi

rm -f -- "$APP_DIR/tic-tac-toe"
rmdir -- "$APP_DIR" 2>/dev/null || true
rm -f -- "$ICON_FILE"

if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database "$HOME/.local/share/applications" >/dev/null 2>&1 || true
fi

echo "Tic-Tac-Toe uninstalled from this user account."
echo "Your source code, release archive, and README were not removed."
