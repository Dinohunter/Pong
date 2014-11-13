#include <cmath>

/*paddle needs to move up and down.
  So paddle needs to have a size, speed (only in y direction)
  velocity(only in y), handle events, render
*/
class Paddle
{
	private:
		// the x and y position of the paddles
		int pPosY;

		//velocity that y will have
		int pVelY;

	public:
		//sets the height and width of the paddles
		static const int PADDLE_WIDTH = 10;
		static const int PADDLE_HEIGHT = 60;

		//sets the speed of the paddles
		static const int PADDLE_VEL = 5;

		Paddle();

		void handleEvent( SDL_Event& event)
};