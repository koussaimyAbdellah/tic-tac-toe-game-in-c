
#!/usr/bin/env bash
set -eu

BIN="$(realpath ./bin/release/game)"

APP_DIR="$HOME/.local/opt/tic-tac-toe"
ICON_DIR="$HOME/.local/share/icons"
MENU_DIR="$HOME/.local/share/applications"

test -x "$BIN" || {
    echo "Executable not found: $BIN"
    exit 1
}

mkdir -p "$APP_DIR" "$ICON_DIR" "$MENU_DIR"

install -m 755 "$BIN" "$APP_DIR/tic-tac-toe"

cat > "$ICON_DIR/tic-tac-toe.svg" <<'SVG'
<svg xmlns="http://www.w3.org/2000/svg"
     width="256" height="256" viewBox="0 0 256 256">
  <rect width="256" height="256" rx="44" fill="#172033"/>
  <g stroke="#dce6f5" stroke-width="9"
     stroke-linecap="round">
    <path d="M96 48 V208 M160 48 V208 M48 96 H208 M48 160 H208"
          fill="none"/>
  </g>
  <path d="M61 58 L87 84 M87 58 L61 84"
        stroke="#61a5fa" stroke-width="9"
        stroke-linecap="round"/>
  <circle cx="192" cy="192" r="19"
          fill="none" stroke="#fb923c" stroke-width="9"/>
</svg>
SVG

cat > "$MENU_DIR/tic-tac-toe.desktop" <<EOF
[Desktop Entry]
Version=1.0
Type=Application
Name=Tic-Tac-Toe
Comment=Play Tic-Tac-Toe in a terminal
Exec=$APP_DIR/tic-tac-toe
Path=$APP_DIR
Icon=$ICON_DIR/tic-tac-toe.svg
Terminal=true
Categories=Game;BoardGame;
EOF

chmod +x "$MENU_DIR/tic-tac-toe.desktop"

DESKTOP_DIR="$(xdg-user-dir DESKTOP 2>/dev/null || true)"

if [ -n "$DESKTOP_DIR" ] && [ -d "$DESKTOP_DIR" ]; then
    cp "$MENU_DIR/tic-tac-toe.desktop" "$DESKTOP_DIR/"
    chmod +x "$DESKTOP_DIR/tic-tac-toe.desktop"
fi

echo "Tic-Tac-Toe launcher created."