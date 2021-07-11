#include "CellPosition.h"
#include "UI_Info.h"
#include "Output.h"


CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	//Done///TODO: Implement this function as described in the .h file (don't forget the validation)
	
	
	
	if (v >= 0 && v <= 8)
	{
		vCell = v;
		return true;
	}
	else {
		
		
		return false; // this line sould be changed with your implementation
		
	}
}

bool CellPosition::SetHCell(int h) 
{
	//Done///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (h >= 0 && h <= 10)
	{
		hCell = h;
		return true;
	}
	else{
		return false; // this line sould be changed with your implementation
	}
}

bool CellPosition::RemoveVCell()
{
	vCell = -1;
	return true;
}

bool CellPosition::RemoveHCell()
{
	hCell = -1;
	return true;
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	//DONE
	///TODO: Implement this function as described in the .h file
	if ((hCell >= 0 && hCell <= 10) && (vCell >=0 && vCell <= 8))
		return true;
	else
 	   return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	//DONE
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it
	///TODO: Implement this function as described in the .h file
	
	int v =8- cellPosition.vCell;
	int h= cellPosition.hCell;
	int cellnum = 1 + (v * 11 + h*1);
	cellPosition.GetCellPositionFromNum(cellnum);
	return cellnum; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	
	if (cellNum >= 1 && cellNum <= 99)
	{
		CellPosition position;
		int V, H;
		//Done/// TODO: Implement this function as described in the .h file
		for (int endrow = 0; endrow <= 88; endrow=endrow + 11)
		{
			if (cellNum > endrow && cellNum <= endrow + 11) {
				V = 8 - (endrow / 11);
				break;
			}
		}

		position.SetVCell(V);
		H = cellNum - ((8 - V) * 11) - 1;
		position.SetHCell(H);

		// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
		//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


		return position;
	}
	
		
}

void CellPosition::AddCellNum (int addedNum)
{
	
	//Done/// TODO: Implement this function as described in the .h file
	int newcellnumber = GetCellNum() + addedNum;
			if (newcellnumber <= 99)
				(*this) = GetCellPositionFromNum(newcellnumber);
	// Note: this function updates the data members (vCell and hCell) of the calling object

}