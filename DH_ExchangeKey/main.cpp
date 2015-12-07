//
//  main.cpp
//  DH_ExchangeKey
//
//  Created by gjwang on 12/7/15.
//  Copyright © 2015 gjwang. All rights reserved.
//

//  Reference https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange

#include <iostream>
#include <math.h>
#include <assert.h>

using namespace::std;

uint64_t powInt(int base, int exponent){
    uint64_t ret = base;
    for (int i=1; i<exponent; i++) {
        ret *= base;
    }
    
    return ret;
}

inline int generatePublicKey(int key, int g, int p){
    return powInt(g, key)%p;
}

inline int generateSharedKey(int publicKey, int privateKey, int p){
    return powInt(publicKey, privateKey)%p;
}

int main(int argc, const char * argv[]) {
    int g = 5, p = 23;
    
    int a = 6;
    int A = generatePublicKey(a, g, p);
    
    int b = 15;
    int B = generatePublicKey(b, g, p);;
    
    int shareA = generateSharedKey(B, a, p);
    int shareB = generateSharedKey(A, b, p);
    
    
    //cout << A << " " << B << endl;
    assert(shareA == shareB);
    std::cout << "shareA=" << shareA << " == shareB=" << shareB << std::endl;
    
    for (int count=0; count<100; count++) {
        int alicePrivateKey = rand()%15 + 1;
        int alicePubliceKey = generatePublicKey(alicePrivateKey, g, p);
        
        int bobPrivateKey = rand()%15 + 1;
        int bobPubliceKey = generatePublicKey(bobPrivateKey, g, p);
        
        int aliceShareKey = generateSharedKey(bobPubliceKey, alicePrivateKey, p);
        int bobShareKey = generateSharedKey(alicePubliceKey, bobPrivateKey, p);
        
        std::cout << "aliceShareKey=" << aliceShareKey <<
                 " == bobShareKey=" << bobShareKey << std::endl;
        assert(aliceShareKey == bobShareKey);
    }
    
    return 0;
}
