#ifndef OD_SY_ENTITY_H
#define OD_SY_ENTITY_H

/**************************************************************************************
* OpenDraft:    System Base Entity Class                                              *
*-------------------------------------------------------------------------------------*
* Filename:     OdEntity.h                                                            *
* Contributors: James Hodgkins                                                        *
* Date:         June 30, 2023                                                         *
* Copyright:    �2023 OpenDraft. All Rights Reserved.                                 *
*-------------------------------------------------------------------------------------*
* Description:                                                                        *
*   Base Entity class for OpenDraft framework.                                        *
***************************************************************************************/


#include <fstream>
#include <string>
#include "System/OdCore.h"
#include "DataManager/OdDbObject.h"
#include "System/Objects/OdLayer.h"


using namespace OD::System;
using namespace OD::Data;


namespace OD
{
	namespace Geometry
	{

		class OdEntity : public OdDbObject {

		private:


		protected:
			int colour = 0;
			int lineType = 0;
			int lineWeight = 0;
			OdLayer* layer = nullptr;


		public:
			OdVector2 location;

			// Constructors & Destructors
			OdEntity() : OdDbObject() {}
			virtual ~OdEntity() = default;

			// Getters & Setters
			OdVector2 getLocation() const;
			void setLocation(OdVector2 aLocation);

			int getColour() const;
			void setColour(int aColour);
			OdColour getDrawColour() const;

			int getLineType() const;
			void setLineType(int aLineType);

			int getLineWeight() const;
			void setLineWeight(int aLineWeight);
			float getDrawLineWeight() const;

			OdLayer* getLayer() const;
			void setLayer(OdLayer* aLayer);
			void setLayer(std::string aLayer);

			// Methods
			virtual void draw(NVGcontext* aContext, OdViewport* aVP) = 0;
			
		};

	} // namespace OD::Geometry
} // namespace OD

#endif // OD_SY_ENTITY_H