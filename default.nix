{
  db4,
  lib,
  meson,
  ninja,
  libxcrypt,
  pkg-config,
  stdenv
}: stdenv.mkDerivation {
  pname = "gendb";
  version = "0";
  src = ./.;
  nativeBuildInputs = [ meson pkg-config ninja ];
  buildInputs = [ db4 libxcrypt ];
  mesonBuildType = "release";
  meta = {
    description = "Utility to create berkeley databases";
    license = lib.licenses.gpl2Plus;
    platforms = lib.platforms.linux;
    mainProgram = "gendb";
  };
}
