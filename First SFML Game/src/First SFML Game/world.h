class World
{
public:
	World();
	~World();
	void update();
	void rotateToVect(sf::Vector2f target);
	void moveToTarget();
	void checkMouseEvents();
};