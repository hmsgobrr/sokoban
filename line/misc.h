#ifndef MISC_H
#define MISC_H

class Warna {
public:
	Warna(unsigned int p_dat) : dat(p_dat) {}
	Warna(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	unsigned int data();
	unsigned char r();
	unsigned char g();
	unsigned char b();
	unsigned char a();
private:
	unsigned int dat;
};

#endif // !MISC_H
