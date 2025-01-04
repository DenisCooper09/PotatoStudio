set(SOURCES
        main.cpp

        Application.cpp
        Window.cpp

        ImGui/Window.cpp
        ImGui/DecoderWindow.cpp
        ImGui/Acceleration3DGraphWindow.cpp
        ImGui/AngularVelocity3DGraphWindow.cpp
        ImGui/PressureAltitudeGraphWindow.cpp

        Decoders/CalibrationDecoder.cpp
        Decoders/DynamicsDecoder.cpp
        Decoders/MPU6050/MPU6050_Decoder.cpp
        Decoders/BME280/BME280_Decoder.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(PotatoStudio ${SOURCES})
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(PotatoStudio WIN32 ${SOURCES})
endif ()
