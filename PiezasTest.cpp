/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

//PASS: Drop from column 0 into (0,0)
TEST(PiezasTest, bottom_row){
	Piezas obj;
	obj.dropPiece(0);
	ASSERT_EQ(obj.pieceAt(0,0), X);
}

//PASS: Drop piece in column 0, check spot (0,2) for blank
TEST(PiezasTest, spot_check){
	Piezas obj;
	obj.dropPiece(0);
	ASSERT_EQ(obj.pieceAt(2,0), Blank);
}

//PASS: Drop piece in column 5; Invalid column
TEST(PiezasTest, out_of_bounds){
	Piezas obj;
	ASSERT_EQ(obj.dropPiece(4), Invalid);
}

//PASS: Invalid Spot check
TEST(PiezasTest, Invalid_spot_check){
	Piezas obj;
	ASSERT_EQ(obj.pieceAt(0, 4), Invalid);
}

//PASS: O places in filled column, next turn should be X
TEST(PiezasTest, O_loses_turn){
	Piezas obj;
	obj.dropPiece(0);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(0);	//x
	obj.dropPiece(0);	//o but blank
	obj.dropPiece(1);	//x
	ASSERT_EQ(obj.pieceAt(0,1), X);
}

//PASS: Tied filled board expected
TEST(PiezasTest, filled_board_tie){
	Piezas obj;
	obj.dropPiece(0);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(0);	//x
	obj.dropPiece(1);	//o
	obj.dropPiece(1);	//x
	obj.dropPiece(1);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(2);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(3);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(3);	//o
	ASSERT_EQ(obj.gameState(), Blank);
}

//PASS: filled board, x wins expected
TEST(PiezasTest, filled_board_x_wins){
	Piezas obj;
	obj.dropPiece(0);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(1);	//x
	obj.dropPiece(1);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(2);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(1);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(2);	//o
	ASSERT_EQ(obj.gameState(), X);
}

//PASS: places piece in filled column, should return Blank
TEST(PiezasTest, filled_column){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(0);
	ASSERT_EQ(obj.dropPiece(0), Blank);
}

//PASS: check game state for unfinished board, returns INVALID
TEST(PiezasTest, unfinished_game){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.dropPiece(0);
	ASSERT_EQ(obj.gameState(), Invalid);
}

//PASS: Check for invalid game after reset
TEST(PiezasTest, board_reset){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.reset();
	ASSERT_EQ(obj.gameState(), Invalid);
}

//PASS: Check piece at spot after reset. Should be blank
TEST(PiezasTest, now_blank){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.reset();
	ASSERT_EQ(obj.pieceAt(0,0), Blank);
}

//FAIL: Should be X starting, not O
TEST(PiezasTest, O_starts){
	Piezas obj;
	ASSERT_EQ(obj.dropPiece(0), O);
}

//FAIL: Should be O's turn, not X's
TEST(PiezasTest, Double_turn){
	Piezas obj;
	obj.dropPiece(0);
	ASSERT_EQ(obj.dropPiece(0), X);
}

//FAIL: Filled board, O wins, not X
TEST(PiezasTest, failed_board_o_wins){
	Piezas obj;
	obj.dropPiece(0);	//x
	obj.dropPiece(1);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(1);	//o
	obj.dropPiece(0);	//x
	obj.dropPiece(2);	//o
	obj.dropPiece(1);	//x
	obj.dropPiece(3);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(3);	//o
	ASSERT_EQ(obj.gameState(), X);
}

//FAIL: Check for piece at spot after reset. Shouldn't be X
TEST(PiezasTest, failed_reset){
	Piezas obj;
	obj.dropPiece(0);
	obj.dropPiece(0);
	obj.reset();
	ASSERT_EQ(obj.pieceAt(0,0), X);
}

//FAIL: Drop piece in column 5; Invalid column
TEST(PiezasTest, fail_out_of_bounds){
	Piezas obj;
	ASSERT_EQ(obj.dropPiece(4), X);
}

//FAIL: X fills board, but yellow wins. Should be X wins
TEST(PiezasTest, O_does_not_win){
	Piezas obj;
	obj.dropPiece(0);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(0);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(1);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(1);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(1);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(2);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(0);	//o
	obj.dropPiece(3);	//x
	obj.dropPiece(0);	//o
	ASSERT_EQ(obj.gameState(), O);
}