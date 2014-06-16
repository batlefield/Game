#ifndef LEVEL_H
#define LEVEL_H
class Level
{

	public:
		Level();
		int loadLevel(std::string path);
		GLuint loadImage(std::string path);
		void addTile(int LevelColor, uint8_t tile, std::string path);	

};
#endif // LEVEL_H
