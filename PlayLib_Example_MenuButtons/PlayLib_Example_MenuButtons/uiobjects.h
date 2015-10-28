typedef struct sposition
{
        float x;
        float y;
} Position;

typedef struct ssize
{
        int width;
        int height;
} Size;

Size screen;
Position middle;

bool IsCollision(Position position, Size size, int x, int y){
        return (x >= position.x && x <= (position.x + size.width) &&
                y >= position.y && y <= (position.y + size.height));
}
