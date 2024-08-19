QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AI.cpp \
        background.cpp \
        funcs.cpp \
        inputbox.cpp \
        main.cpp \
        menu.cpp \
        players.cpp \
        pongball.cpp \
        sound.cpp \
        window.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /home/duongnh/Downloads/SFML-2.6.1-linux-gcc-64-bit/SFML-2.6.1/include/
LIBS += -L/home/duongnh/Downloads/SFML-2.6.1-linux-gcc-64-bit/SFML-2.6.1/lib/ -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-audio

DISTFILES += \
    CMakeLists.txt \
    LICENSE \
    README.md \
    bin/executable.exe \
    bin/gfx/background.png \
    bin/gfx/creator-logo.png \
    bin/gfx/explode.png \
    bin/gfx/font/november.ttf \
    bin/gfx/game-logo.png \
    bin/gfx/icon.ico \
    bin/gfx/menu-background.png \
    bin/gfx/mouse-pointer.png \
    bin/gfx/pause-background.png \
    bin/gfx/player-shadow.png \
    bin/gfx/player1-shadow.png \
    bin/gfx/player1.png \
    bin/gfx/player2.png \
    bin/gfx/pongball.png \
    bin/openal32.dll \
    bin/sfml-audio-2.dll \
    bin/sfml-audio-d-2.dll \
    bin/sfml-graphics-2.dll \
    bin/sfml-graphics-d-2.dll \
    bin/sfml-network-2.dll \
    bin/sfml-network-d-2.dll \
    bin/sfml-system-2.dll \
    bin/sfml-system-d-2.dll \
    bin/sfml-window-2.dll \
    bin/sfml-window-d-2.dll \
    bin/sfx/blip.wav \
    bin/sfx/clapps.wav \
    bin/sfx/player-move.wav \
    bin/sfx/player1-scores.wav \
    bin/sfx/player2-scores.wav \
    bin/sfx/pong-outside.wav \
    bin/sfx/pong-table.wav \
    bin/sfx/pong.wav \
    bin/sfx/quit.wav \
    bin/sfx/select.wav \
    lib/cmake/SFML/SFMLConfig.cmake \
    lib/cmake/SFML/SFMLConfigDependencies.cmake \
    lib/cmake/SFML/SFMLConfigVersion.cmake \
    lib/cmake/SFML/SFMLSharedTargets-debug.cmake \
    lib/cmake/SFML/SFMLSharedTargets-release.cmake \
    lib/cmake/SFML/SFMLSharedTargets.cmake \
    lib/cmake/SFML/SFMLStaticTargets-debug.cmake \
    lib/cmake/SFML/SFMLStaticTargets-release.cmake \
    lib/cmake/SFML/SFMLStaticTargets.cmake \
    lib/libFLAC.a \
    lib/libfreetype.a \
    lib/libogg.a \
    lib/libopenal32.a \
    lib/libsfml-audio-d.a \
    lib/libsfml-audio-s-d.a \
    lib/libsfml-audio-s.a \
    lib/libsfml-audio.a \
    lib/libsfml-graphics-d.a \
    lib/libsfml-graphics-s-d.a \
    lib/libsfml-graphics-s.a \
    lib/libsfml-graphics.a \
    lib/libsfml-main-d.a \
    lib/libsfml-main.a \
    lib/libsfml-network-d.a \
    lib/libsfml-network-s-d.a \
    lib/libsfml-network-s.a \
    lib/libsfml-network.a \
    lib/libsfml-system-d.a \
    lib/libsfml-system-s-d.a \
    lib/libsfml-system-s.a \
    lib/libsfml-system.a \
    lib/libsfml-window-d.a \
    lib/libsfml-window-s-d.a \
    lib/libsfml-window-s.a \
    lib/libsfml-window.a \
    lib/libvorbis.a \
    lib/libvorbisenc.a \
    lib/libvorbisfile.a

HEADERS += \
    include/AI.hpp \
    include/background.hpp \
    include/constants.hpp \
    include/funcs.hpp \
    include/menu.hpp \
    include/players.hpp \
    include/pongball.hpp \
    include/rect.hpp \
    include/sound.hpp \
    include/window.hpp \
    inputbox.h
