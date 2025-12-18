{
  description = "QMK firmware development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        devShells.default = pkgs.mkShell {
          name = "qmk-dev-shell";

          buildInputs = [
            # QMK CLI
            pkgs.qmk

            # AVR toolchain — THIS IS ENOUGH
            pkgs.pkgsCross.avr.buildPackages.gcc
            pkgs.pkgsCross.avr.buildPackages.binutils

            # ARM toolchain
            pkgs.gcc-arm-embedded

            # Flashing tools
            pkgs.dfu-programmer
            pkgs.dfu-util

            # Python deps QMK uses
            (pkgs.python3.withPackages (ps: with ps; [
              pyserial
              pillow
              hid
            ]))

            # Utilities
            pkgs.git
            pkgs.usbutils
          ];

          shellHook = ''
            echo "⌨️  QMK dev shell ready"
            echo "AVR GCC: $(avr-gcc --version | head -n1)"
          '';
        };
      }
    );
}

