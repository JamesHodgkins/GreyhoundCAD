#ifndef OD_SY_CIRCLE_H
#define OD_SY_CIRCLE_H

/**************************************************************************************
* OpenDraft:    System Circle Entity Class                                            *
*-------------------------------------------------------------------------------------*
* Filename:     OdCircle.h                                                            *
* Contributors: James Hodgkins                                                        *
* Date:         June 27, 2023                                                         *
* Copyright:    �2023 OpenDraft. All Rights Reserved.                                 *
*-------------------------------------------------------------------------------------*
* Description:                                                                        *
*   Circle Entity class for OpenDraft framework.                                      *
***************************************************************************************/


#include "System/Entities/OdEntity.h"


using namespace OD::System;

namespace OD
{
	namespace Geometry
	{

		class OdCircle : public OdEntity {
		public:
			double radius;


			// Override Get Type
			const char* getType() const
			{
				// Return type
				return "Circle";
			}


			// Serialisation Methods
			virtual void serialise(std::wstring& buffer)
			{
				// For each property, add to buffer

				// Add type code
				buffer += L"E002";

				// Serialise handle
				buffer += std::to_wstring(getHandle());

				// Serialise location
				buffer += std::to_wstring(location.x);
				buffer += std::to_wstring(location.y);

				// Serialise radius
				buffer += std::to_wstring(radius);
			}

			virtual void deserialise(std::wstring buffer)
			{

			}



			//
			// Constructors
			//
			
			OdCircle()
			{
				location = OdVector2(0, 0);
				radius = 1;
			}

			OdCircle(OdVector2 aCentre, double aRadius)
			{
				location = aCentre;
				radius = aRadius;
			}

			OdCircle(float x, float y, double aRadius)
			{
				location = OdVector2(x, y);
				radius = aRadius;
			}

			OdCircle(int x, int y, double aRadius)
			{
				location = OdVector2(x, y);
				radius = aRadius;
			}


			//
			// Draw
			//

			void draw(NVGcontext* aContext, const OdVector2* aView) override
			{
				// To do: get line weight from layer
				//int lineWidthIndex = getLineWeight();
				//float lineWeight = OdSystem::getRegistryVariableByName("lineWidth");

				OdColour drawColour = getDrawColour();

				nvgBeginPath(aContext);
				nvgCircle(aContext, location.x + aView->x, location.y + aView->y, radius);
				nvgStrokeColor(aContext, drawColour.asNvgColour());
				nvgStrokeWidth(aContext, 3);
				nvgStroke(aContext);
			}

			//
			// Calculated Properties
			//

			// Area
			double getArea()
			{
				return OD_PI * radius * radius;
			}

			// Set by Area
			void setArea(double anArea)
			{
				radius = sqrt(anArea / OD_PI);
			}

			// Circumference
			double getCircumference()
			{
				return 2 * OD_PI * radius;
			}

			// Set by Circumference
			void setCircumference(double aCircumference)
			{
				radius = aCircumference / (2 * OD_PI);
			}

			// Get Diameter
			double getDiameter()
			{
				return 2 * radius;
			}

			// Set Diameter
			void setDiameter(double aDiameter)
			{
				radius = aDiameter / 2;
			}

		};
	}
}


#endif // OD_SY_CIRCLE_H