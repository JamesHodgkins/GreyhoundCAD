#pragma once

/**************************************************************************************
* OpenDraft:    Core System Resource Manager Class                                    *
*-------------------------------------------------------------------------------------*
* Filename:     OdSyResourceManager.h                                                 *
* Contributors: James Hodgkins                                                        *
* Date:         June 17, 2023                                                         *
* Copyright:    �2023 OpenDraft. All Rights Reserved.                                 *
*-------------------------------------------------------------------------------------*
* Description:                                                                        *
*   Central manager for system resources (images, fonts etc)                          *
***************************************************************************************/



#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>
#include "System/Utils/OdSyImage.h"


class OdSyResourceManager
{
public:
	std::unordered_map<std::string, OdSyFont*> fonts;
	std::unordered_map<std::string, OdSyImage*> images;


	void importDirectory(NVGcontext* vg, const std::vector<std::string>& exts, const char* directory)
	{
		std::cout << "LOAD DIR STARTED" << std::endl;
		std::filesystem::directory_iterator end_itr; // Default constructor provides an end iterator

		// Iterate over each entry in the specified directory
		for (std::filesystem::directory_iterator itr(directory); itr != end_itr; ++itr)
		{
			// Check if the current entry is a regular file
			if (std::filesystem::is_regular_file(itr->path()))
			{
				// Extract the file extension of the current file
				std::string fileExtension = itr->path().extension().string();

				// Compare the file extension against the given extensions in the vector
				for (const std::string& ext : exts)
				{
					
					if (fileExtension == "." + ext)
					{
						std::cout << itr->path().string() << std::endl;
						std::cout << itr->path().stem().string() << std::endl;
						// If the file extension matches one of the given extensions, process the file
						importImageFromFile(vg, 32, 32, itr->path().filename().string().c_str(), itr->path().string().c_str());
						break;
					}
				}
			}
		}
	}



	// Import an image into the resource manager
	// If an image with the same reference already exists, return a pointer to it
	// Otherwise, create a new image and store it in the resource manager, then return a pointer to it
	OdSyImage* importImageFromFile(NVGcontext* vg, int width, int height, const char* reference, const char* filePath)
	{
		// Check if an image with the given reference already exists
		std::unordered_map<std::string, OdSyImage*>::iterator imageIter = images.find(reference);
		if (imageIter != images.end())
		{
			// Image with the same reference already exists, return a pointer to it
			return imageIter->second;
		}

		// Image with the given reference does not exist, create a new image
		int imageHandle = nvgCreateImage(vg, filePath, 0);
		OdSyImage* newImage = new OdSyImage(width, height, 1.0, filePath, imageHandle);

		// Store the new image in the resource manager
		images[reference] = newImage;

		// Return a pointer to the new image
		return newImage;
	}



	// Import an font into the resource manager
	// If an font with the same reference already exists, return a pointer to it
	// Otherwise, create a new font and store it in the resource manager, then return a pointer to it
	OdSyFont* importFontFromFile(NVGcontext* vg, const char* reference, const char* filePath)
	{
		// Check if an font with the given reference already exists
		std::unordered_map<std::string, OdSyFont*>::iterator fontIter = fonts.find(reference);
		if (fontIter != fonts.end())
		{
			// font with the same reference already exists, return a pointer to it
			return fontIter->second;
		}

		// font with the given reference does not exist, create a new font
		int fontHandle = nvgCreateFont(vg, reference, filePath);
		OdSyFont* newFont = new OdSyFont(reference, filePath, fontHandle);

		// Store the new font in the resource manager
		fonts[reference] = newFont;

		// Return a pointer to the new font
		return newFont;
	}
};