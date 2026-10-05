{
  description = "Very crappy utility to create berkeley databases";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem ( system:
      let
        pkgs = import nixpkgs { inherit system; };
	lib = pkgs.lib;
      in
      rec {
        packages.default = lib.customisation.callPackageWith pkgs ./default.nix {};
        devShells.default = pkgs.mkShell {
	  inputsFrom = [ packages.default ];
	  mesonBuildType = "debug";
        };
      }
    );
}
