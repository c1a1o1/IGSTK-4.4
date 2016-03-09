/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    $RCSfile: igstkBoxObjectTest.cxx,v $
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
  representation->RequestSetBoxObject( object );


#include "igstkBoxObject.h"
#include "igstkBoxObjectRepresentation.h"
#include "igstkSpatialObjectTestHelper.h"


int igstkBoxObjectTest( int, char * [] )
{

  typedef igstk::BoxObject                ObjectType;
  typedef igstk::BoxObjectRepresentation  RepresentationType;

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
  std::cout << "Testing Set/GetSize() : ";
  igstk::BoxObject::ArrayType size;
  size[0] = 10;
  size[1] = 20;
  size[2] = 30;
  object->SetSize(size);

  igstk::BoxObject::ArrayType sizeRead = object->GetSize();
  for(unsigned int i=0;i<3;i++)
    {
    if(sizeRead[i] != size[i])
      {
      std::cerr << "Size error : " << sizeRead[i] << " v.s " << size 
                << std::endl; 
      return EXIT_FAILURE;
      }
    }

  size[0] = 11;
  size[1] = 22;
  size[2] = 33;
  object->SetSize(size[0],size[1],size[2]);
  sizeRead = object->GetSize();
  for(unsigned int i=0;i<3;i++)
    {
    if(sizeRead[i] != size[i])
      {
      std::cerr << "Size error : " << sizeRead[i] << " v.s " << size 
                << std::endl; 
      return EXIT_FAILURE;
      }
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
  object->SetSize( 20.0, 30.0, 40.0 );

  representation->SetColor(0.3,0.7,0.2);
  
  testHelper.TestRepresentationCopy();
  testHelper.ExerciseScreenShot();

  return testHelper.GetFinalTestStatus();
}
