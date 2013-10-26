
using namespace std;

//#define get(a) int Get

class Object 
{
public:
	int GetWeight() { return m_Weight; }
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }

	void SetWeight(int w) {m_Weight = w;}
	void SetWidth(int w) {m_Width = w;}
	void SetHeight(int h) {m_Height = h;}

private:
	int m_Weight;
	int m_Width;
	int m_Height;
	enum m_Colour;
};