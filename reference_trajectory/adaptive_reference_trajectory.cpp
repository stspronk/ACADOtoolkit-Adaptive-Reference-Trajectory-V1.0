/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2014 by Boris Houska, Hans Joachim Ferreau,
 *    Milan Vukov, Rien Quirynen, KU Leuven.
 *    Developed within the Optimization in Engineering Center (OPTEC)
 *    under supervision of Moritz Diehl. All rights reserved.
 *
 *    ACADO Toolkit is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with ACADO Toolkit; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


/**
 *    \file src/reference_trajectory/adaptive_reference_trajectory.cpp
 *    \author Hans Joachim Ferreau, Boris Houska
 *    \date 13.06.2008
 */


#include <acado/reference_trajectory/adaptive_reference_trajectory.hpp>

using namespace std;



BEGIN_NAMESPACE_ACADO
//
// GLOBAL VARIABLE TO TRACK REFERENCE
//
//static int CurrentObjective=0;
//bool end_flag = false;
//int CurrentObjective =0;
// PUBLIC MEMBER FUNCTIONS:
//



AdaptiveReferenceTrajectory::AdaptiveReferenceTrajectory( ) : ReferenceTrajectory( )
{
	CurrentObjective = 0;
	ObjectiveEndFlag = false;
}


AdaptiveReferenceTrajectory::AdaptiveReferenceTrajectory( const VariablesGrid& _yRef
                                                            ) 
{
	if ( _yRef.isEmpty( ) == BT_TRUE )
	{
		ACADOERROR( RET_INVALID_ARGUMENTS );
		ASSERT( 1==0 );
	}
	
// 	yRef.add( _yRef );
	//CurrentObjective = rhs.CurrentObjective;
	yRef = _yRef;
	
	//setStatus( BS_READY );
	CurrentObjective = 0;
	ObjectiveEndFlag = false;
}


AdaptiveReferenceTrajectory::AdaptiveReferenceTrajectory( const char* const _yRefFileName
															) 
{
	VariablesGrid _yRef;
    _yRef.read( _yRefFileName );

	if ( _yRef.isEmpty( ) == BT_TRUE )
	{
		ACADOERROR( RET_FILE_CAN_NOT_BE_OPENED );
		ASSERT( 1==0 );
	}
	
// 	yRef.add( _yRef );
	yRef = _yRef;
	//setStatus( BS_READY );
	CurrentObjective = 0;
	ObjectiveEndFlag = false;

}

AdaptiveReferenceTrajectory::AdaptiveReferenceTrajectory( const AdaptiveReferenceTrajectory& rhs ) : ReferenceTrajectory( rhs )
{
	yRef = rhs.yRef;
	
	CurrentObjective = rhs.CurrentObjective;
	ObjectiveEndFlag = rhs.ObjectiveEndFlag;
}

AdaptiveReferenceTrajectory::~AdaptiveReferenceTrajectory( )
{
}


AdaptiveReferenceTrajectory& AdaptiveReferenceTrajectory::operator=( const AdaptiveReferenceTrajectory& rhs )
{
	if ( this != &rhs )
	{
		ReferenceTrajectory::operator=( rhs );
		
		
		yRef = rhs.yRef;
		
		CurrentObjective = rhs.CurrentObjective;
		ObjectiveEndFlag = rhs.ObjectiveEndFlag;
	}

    return *this;
}



ReferenceTrajectory* AdaptiveReferenceTrajectory::clone( ) const
{
	return new AdaptiveReferenceTrajectory( *this );
}




returnValue AdaptiveReferenceTrajectory::init(	double startTime,
												const DVector& _x,
												const DVector& _xa,
												const DVector& _u,
												const DVector& _p,
												const DVector& _w
												)
{
	return SUCCESSFUL_RETURN;
}


returnValue AdaptiveReferenceTrajectory::step(	double _currentTime,
												const DVector& _y,
												const DVector& _x,
												const DVector& _xa,
												const DVector& _u,
												const DVector& _p,
												const DVector& _w
												)
{
	return SUCCESSFUL_RETURN;
}


returnValue AdaptiveReferenceTrajectory::step(	const DVector& _x,
												const VariablesGrid& _u,
												const VariablesGrid& _p,
												const VariablesGrid& _w
												)
{
	return SUCCESSFUL_RETURN;
}

//returnValue AdaptiveReferenceTrajectory::check(  const VariablesGrid& _yRef,
//                                                 const DVector& _x
//)
//{
//    
//}



returnValue AdaptiveReferenceTrajectory::getReference( 	double tStart,
														double tEnd,
														VariablesGrid& _yRef,
														DVector _xEst
														) const
// CHECK x(states) vs x_ref(yref) and if difference is small enough next reference
{
	//uint checklist = yRef.getNumRows() - 1;
	//uint Current_Objective_Counter = 0;
	//if (check < 3)
	//{
	//thread_local int CurrentObjective = 0;	
	
	printf( "\n*** Current Objective = %d  ***\n",CurrentObjective );
	
	//printf( "\n*** number of yRef columns = %d  ***\n", yRef.getDim()/yRef.getNumRows() );
	
	//}
	
			//}// checklist
			//if(Current_Objective + 1 == yRef.getNumCols())
			//{
			//	end_flag = true;
			//}

	//Grid grid(tStart,tEnd);
	//_yRef.init( yRef.getVector(CurrentObjective),grid );
	//printf( "\n***Current start time = %f  ***\n",tStart );
	//printf( "\n***Current end time = %f  ***\n",tEnd );
	///if (CurrentObjective < 2)
	//{
	//	++CurrentObjective;
	//}	



	//printf( "\n*** ref check = %d  ***\n", yRef.getVector(0) == yRef.getVector(2) );
	if (ObjectiveEndFlag != true)
	{
		if (_xEst.isEmpty() != BT_TRUE) //look for trajectory update
		{
			//printf( "\n*** passed x position = %f  ***\n", _xEst[2] );
			//printf( "\n*** ref x position = %f  ***\n", yRef.getVector(CurrentObjective)[2]);

			int Current_Objective_Counter = 0;
			DVector yCurrent = yRef.getVector(CurrentObjective);
			for( uint i=0; i<3; ++i )
			{
				//if ( ( abs( _xEst[i] - yCurrent[i])) <= (abs( 0.05*yCurrent[i])) )//&& ( abs(_xEst[i]) <= (abs( 0.05*yCurrent[i])))
				if (yCurrent[i] == 0.0)
				{
					if ( (_xEst[i] <= 0.05) && (_xEst[i] > -0.05) )
					{
						printf( "\n*** ccepted %d position = %f  ***\n",i, _xEst[i] );
						printf( "\n*** ref %d position = %f  ***\n",i, yRef.getVector(CurrentObjective)[i]);
						++Current_Objective_Counter;
						printf( "\n*** check counter = %d  ***\n", Current_Objective_Counter);
					}
					else
					{
						printf( "\n*** rejected %d position = %f  ***\n",i, _xEst[i] );
						printf( "\n*** ref %d position = %f  ***\n",i, yRef.getVector(CurrentObjective)[i]);	
					}
				}
				else
				{
					if (  ( abs(_xEst[i]) >= abs(0.95*yCurrent[i])) && ( abs(_xEst[i]) <= abs(1.05*yCurrent[i])) )
					{
						printf( "\n*** accepted %d position = %f  ***\n",i, _xEst[i] );
						printf( "\n*** ref %d position = %f  ***\n",i, yRef.getVector(CurrentObjective)[i]);
						++Current_Objective_Counter;
						printf( "\n*** check counter = %d  ***\n", Current_Objective_Counter);
					}
					else
					{
						printf( "\n*** rejected %d position = %f  ***\n",i, _xEst[i] );
						printf( "\n*** ref %d position = %f  ***\n",i, yRef.getVector(CurrentObjective)[i]);	
					}
				} 
			}

			if ( Current_Objective_Counter == 3 )
			{
				++CurrentObjective;
			}// checklist
			
			if(CurrentObjective == yRef.getDim()/yRef.getNumRows() - 1) // getNumCols() doesnt return the right value for some reason
			{
				ObjectiveEndFlag = true;
			}
			
			Grid grid(tStart,tEnd);
			_yRef.init( yRef.getVector(CurrentObjective),grid );
		}
		else // if preperationstep controller step with empty xest dont update
		{
			Grid grid(tStart,tEnd);
			_yRef.init( yRef.getVector(CurrentObjective),grid );
		}
		
			
	}
	else
	{
		Grid grid(tStart,tEnd);
		_yRef.init( yRef.getLastVector(),grid );
	}
	/*uint checklist = yRef.getNumCols( ) -1;
	}
    
    uint Current_Objective_Counter = 0;
    estimator = &_estimator;
	
		

	if ( estimator.getX( xEst) != SUCCESSFUL_RETURN )
		return ACADOERROR( RET_REFERENCE_GET_FAILED );
		
	if ( acadoIsEqual( xEst.getDim(), yRef.getNumCols() ) == BT_FALSE )
	  	return ACADOERROR( RET_INVALID_ARGUMENTS );
	
    if (end_flag != true)
    {
		for( uint i=0; i<checklist; ++i )
			if ( acadoIsStrictlyGreater ( abs( xEst[i] - yRef.getVector(Current_Objective)[i]), abs( 0.05*yRef.getVector(Current_Objective)[i] ) ) == BT_TRUE)
				{
					Current_Objective_Counter++;
				} // checklist
		
		if ( Current_Objective_Counter == checklist )
		{
			Current_Objective++;
		}// checklist
		
		if(Current_Objective + 1 == yRef.getNumRows())
		{
			end_flag = true;
			Grid grid(tStart,tEnd);
			_yRef.init( yRef.getFirstVector(),grid );
			return SUCCESSFUL_RETURN;
		}	

        if (Current_Objective == 0)
        {
			Grid grid(tStart,tEnd);
            _yRef.init( yRef.getFirstVector(),grid );
        }
        else
        {
			Grid grid(tStart,tEnd);
            _yRef.init( yRef.getVector(Current_Objective),grid );
        }
    }// end flag
    // constant extrapolation beyond end of interval
    else
    {
        Grid grid(tStart,tEnd);
		_yRef.init( yRef.getFirstVector(),grid );
	}*/

	return SUCCESSFUL_RETURN;
}

uint AdaptiveReferenceTrajectory::getDim( ) const
{
	return yRef.getNumValues( );
}

/*void AdaptiveReferenceTrajectory::UpdateObjective()
{
	CurrentObjective++;
}*/



/*returnValue AdaptiveReferenceTrajectory::getStateEstimates(	DVector& _xSAJUUK
															) const
{
	VariablesGrid AllStates;

	if(process->getY(AllStates) == SUCCESSFUL_RETURN)
	{
		_xSAJUUK = AllStates.getLastVector();
	}
	else
	{
		return RET_CONTROLLER_STEP_FAILED;		
	}
	return SUCCESSFUL_RETURN;
}*/


CLOSE_NAMESPACE_ACADO

// end of file.
