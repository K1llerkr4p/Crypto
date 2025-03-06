#include <iostream>
#include <vector>
#include <string>
#include <cryptlib.h>
#include <hex.h>
#include <filters.h>
#include <osrng.h>
#include <secblock.h>

using namespace std;
using namespace CryptoPP;

// Función para convertir una cadena hexadecimal a un vector de bytes
vector<CryptoPP::byte> hexToBytes(const string& hex) {
    vector<CryptoPP::byte> bytes;
    StringSource(hex, true, new HexDecoder(new VectorSink(bytes)));
    return bytes;
}

// Función XOR
vector<CryptoPP::byte> xorBytes(const vector<CryptoPP::byte>& a, const vector<CryptoPP::byte>& b) {
    vector<CryptoPP::byte> result(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        result[i] = a[i] ^ b[i % b.size()];
    }
    return result;
}

int main() {
    vector<vector<CryptoPP::byte>> ciphers(12); // Tamaño correcto
    ciphers[0] = hexToBytes("72212b29402b66342437255717562d652e5748692f2452206b17153b36364b2236172f2b372b2a2c2c6f2d6e3e3347");
    ciphers[1] = hexToBytes("5a74202b412f243123743459175c3737394b1224382f5d332244747436364b35365b3426276a3d762e2e206e273f46312a30203b");
    ciphers[2] = hexToBytes("752122394f23233e39316d555e412c653949472c21295732674537272621572579170b2b742e21762720226e192f582726263527");
    ciphers[3] = hexToBytes("403b283d412722316d356d4d5952632d2d555b25212456352217313a21235d35345e21296e6a2837633c29203e2854653a74323d23");
    ciphers[4] = hexToBytes("7e3b213d463a277039213b5717423620784b473a3d2056252245782727734c3725522f67302f643b2c23293c7137542c39");
    ciphers[5] = hexToBytes("5e353731512166316d253851525d63373d4b422623215d336b17303d38324b7636172226276a3523266f282b333515212226");
    ciphers[6] = hexToBytes("62212c2b5a6e212224202c4a174a63362d18553b2431576121423d74213c5e3934562a28743a2b246320383c307a572a2035");
    ciphers[7] = hexToBytes("63313737153a233e292624591b1337243418442c37654d2f675f313e3d735c3377553b223a2b642522212b3c34");
    ciphers[8] = hexToBytes("13382a2b152d2e393f26245c584063213d1842263f31572f224478252736182532172f25262f2a7a632a206e3b3b51202c");
    ciphers[9] = hexToBytes("7274353d462f347029316d5d44472c3678515c2a24215d2f33522b743e3c4b76395e2028276a212422216c273f2950352226202a3c5040");
    ciphers[10] = hexToBytes("603d65365a6e35356d38281854462e35345153276d364d3267543924203a5b3e38446e65382f6432222d2d6e323254332620206a");
    ciphers[11] = hexToBytes("7b353c78522b282428743c4d52132d2a784c5b2c23201824344337393334577627563c26742f3722266f232838395c2a");

    vector<CryptoPP::byte> goal = hexToBytes("62212078533c2f313e743e5759132f242b185f282324562034173d3a7210512333562a67062f253a");
    vector<vector<CryptoPP::byte>> processed;

    for (const auto& cipher : ciphers) {
        processed.push_back(xorBytes(cipher, goal));
    }

    string palabra;
    cout << "Introduce palabra: ";
    getline(cin, palabra);

    vector<CryptoPP::byte> palabraBytes(palabra.begin(), palabra.end());

    for (const auto& proc : processed) {
        if (proc.size() < palabraBytes.size()) continue; // Evita desbordamientos

        for (size_t j = 0; j <= proc.size() - palabraBytes.size(); j++) {
            vector<CryptoPP::byte> word = xorBytes(palabraBytes, vector<CryptoPP::byte>(proc.begin() + j, proc.begin() + j + palabraBytes.size()));

            bool flag = true;
            for (CryptoPP::byte c : word) {
                if (!isalpha(static_cast<unsigned char>(c)) && c != ' ' && c != ',') {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                cout << "\n" << string(word.begin(), word.end()) << endl;
            }
        }
    }

    vector<CryptoPP::byte> palabraFinal = {'Q', 'u', 'e', ' ', 'f', 'r', 'i', 'a', 's', ' ', 's', 'o', 'n', ' ', 'l', 'a', 's', ' ', 'm', 'a', 'n', 'a', 'n', 'a', 's', ' ', 'e', 'n', ' ', 'C', 'i', 'u', 'd', 'a', 'd', ' ', 'R', 'e', 'a', 'l', '!'};
    vector<CryptoPP::byte> llave = xorBytes(goal, vector<CryptoPP::byte>(palabraFinal.begin(), palabraFinal.begin() + goal.size()));

    cout << "\nLlave recuperada: ";
    for (CryptoPP::byte b : llave) cout << hex << (int)(b & 0xFF) << " ";
    cout << endl;

    for (const auto& cipher : ciphers) {
        if (cipher.size() < llave.size()) continue; // Evita desbordamientos
        vector<CryptoPP::byte> mensaje = xorBytes(llave, vector<CryptoPP::byte>(cipher.begin(), cipher.begin() + llave.size()));
        cout << "Mensaje: " << string(mensaje.begin(), mensaje.end()) << endl;
    }

    vector<CryptoPP::byte> mensajeFinal = xorBytes(llave, goal);
    cout << "Mensaje: " << string(mensajeFinal.begin(), mensajeFinal.end()) << endl;

    return 0;
}
