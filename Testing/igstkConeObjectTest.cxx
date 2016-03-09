/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    $RCSfile: igstkConeObjectTest.cxx,v $
  Language:  C++
  Date:      $Date: 2008-02-11 01:41:51 $
  Version:   $Revision: 1.11 $

  Copyright (c) ISC  Insight Software Consortium.  All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#if defined(_MSC_VER)
// Warning about: identifier was truncated to '255' characters 
// in the debug information (MVC6.0 Debug)
#pragma warning( disable : 4786 )
#endif

#ifdef ConnectObjectToRepresentationMacro
#undef ConnectObjectToRepresentationMacro
#endif

#define ConnectObjectToRepresentationMacro( object, representation ) \
  representation->RequestSetConeObject( object );


#include "igstkConeObject.h"
#include "igstkConeObjectRepresentation.h"
#include "igstkSpatialObjectTestHelper.h"


int igstkConeObjectTest( int, char * [] )
{

  typedef igstk::ConeObject                ObjectType;
  typedef igstk::ConeObjectRepresentation  RepresentationType;

  typedef igstk::SpatialObjectTestHelper<
    ObjectType, RepresentationType > TestHelperType;

  //
  // The helper constructor intializes all the elements needed for the test.
  //
  TestHelperType  testHelper;

  ObjectType         * object         = testHelper.GetSpatialObject();
  RepresentationType * representation = testHelper.GetRepresentation();

  //
  //  Tests that are specific to this type of SpatialObject
  //
  //
  // Test Set/Get() Parameters
  std::cout << "Testing Set/GetRadius() : ";
  object->SetRadius(3.2);

  double radiusRead = object->GetRadius();
  if(radiusRead != 3.2)
    {
    std::cerr << "Radius error : " << radiusRead << " v.s " 
              << 3.2 << std::endl; 
    return EXIT_FAILURE;
    }
  std::cout << "[PASSED]" << std::endl;

  // Test Set/GetHeight()
  std::cout << "Testing Set/GetHeight() : ";
  object->SetHeight(4.1);

  double heightRead = object->GetHeight();
  if(heightRead != 4.1)
    {
    std::cerr << "Height error : " << heightRead << " v.s " 
              << 4.1 << std::endl; 
    return EXIT_FAILURE;
    }
  std::cout << "[PASSED]" << std::endl;


  testHelper.TestRepresentationProperties();
  testHelper.ExercisePrintSelf();
  testHelper.TestTransform();
  testHelper.ExerciseDisplay();

  // Testing UpdateRepresentationFromGeometry. Changing the Spatial Object
  // geometrical parameters should trigger an update in the representation
  // class.
  std::cout << "Testing UpdateRepresentationFromGeometry() : ";
  object->SetRadius( 10.0 );
  object->SetHeight( 17.0 );

  representation->SetColor(0.3,0.7,0.2);
  
  testHelper.TestRepresentationCopy();
  testHelper.ExerciseScreenShot();

  return testHelper.GetFinalTestStatus();
}
