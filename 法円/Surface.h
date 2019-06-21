#pragma once
#include <deque>
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

class Surface24 {

public:
	struct RGB{
		std::uint8_t B = 0;
		std::uint8_t G = 0;
		std::uint8_t R = 0;
	};
	
	typedef std::deque<std::vector<RGB>> Surface;
	typedef std::int16_t Cood;

	Surface24() {
		Resize(1, 1);
	}
	Surface24(const Cood& Width_, const Cood& Height_) {
		Resize(Width_, Height_);

	}

	bool Resize(const Cood& Width_, const Cood Height_) {
		S.resize(Height_);
		for (auto& o: S) {
			o.resize(Width_);
		}
		W = Width_;
		H = Height_;
		return true;
	}
	RGB Index(const Cood& X, const Cood& Y) const {
		return S[Y][X];
	}
	RGB& Index(const Cood& X, const Cood& Y){
		return S[Y][X];
	}

	Cood Width() const{
		return W;
	}
	Cood Height()const {
		return H;
	}

protected:
	Surface S;
	std::size_t W = 0;
	std::size_t H = 0;

};

bool SaveBMP(const Surface24& S,const std::string& Name) {

	std::ofstream ofs(Name,std::ios::binary);

	std::uint16_t word = 0;
	std::uint32_t dword = 0;
	int Pad = ((S.Width()*3) % 4);

	//file hedder.
	word = 'B' | 'M' << 8;
	ofs.write((char*)&word, 2);
	dword = 54+(S.Height()*(S.Width()*3+Pad));
	//dword = 54+(S.Height()*S.Width()*3);
	ofs.write((char*)&dword, 4);
	word =0;
	ofs.write((char*)&word, 2);
	ofs.write((char*)&word, 2);
	dword = 54;
	ofs.write((char*)&dword, 4);
	//info header.
	dword = 40;
	ofs.write((char*)&dword, 4);//size
	dword = S.Width();
	ofs.write((char*)&dword, 4);//width
	dword = S.Height();
	ofs.write((char*)&dword, 4);//height
	word = 1;
	ofs.write((char*)&word, 2);//plane
	word = 24;
	ofs.write((char*)&word, 2);//bit
	dword = 0;
	ofs.write((char*)&dword, 4);//compress
	dword = (S.Height()*(S.Width()*3+Pad));
	ofs.write((char*)&dword, 4);//image size

	dword =0;
	ofs.write((char*)&dword, 4);//xpixbymeter
	ofs.write((char*)&dword, 4);//ypixbymeter
	ofs.write((char*)&dword, 4);//color used
	ofs.write((char*)&dword, 4);//important color


	dword = 0;

	for (std::size_t y = 0; y < S.Height(); y++) {
		for (std::size_t x = 0; x < S.Width(); x++) {
			ofs.write((char*)& S.Index(x, S.Height() - y - 1), 3);
		}
		for (int i = Pad; i < 4 && Pad != 0; i++) {
			std::uint8_t P = 0;
			ofs.write((char*)& P, 1);
		}
	}
	return true;
}