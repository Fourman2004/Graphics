#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>
//texture ID
unsigned int Texture;

using namespace std;

/// <summary>
/// <para></para>
/// <para></para>
/// <para></para>
/// <para></para>
/// </summary>
/// <param name="SourceTexture"> - Texture File</param>
/// <param name="height"> - The height of the texture</param>
/// <param name="width"> - the width of the texture</param>
/// <param name="Channels"> - the amount of colour channels it will have</param>
/// <param name="flip"> - a bool that will vertically flip the texture</param>
/// <returns></returns>
int Textureshape(const char* SourceTexture, int height, int width, int Channels, bool flip)
{