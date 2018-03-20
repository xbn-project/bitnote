// Copyright (c) 2018, The Bitnote Developers.
// Portions Copyright (c) 2012-2013, The CryptoNote Developers.
//
// All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "crypto/crypto.h"
#include "cryptonote_core/cryptonote_basic.h"

#include "single_tx_test_base.h"

class test_generate_key_image : public single_tx_test_base
{
public:
  static const size_t loop_count = 1000;

  bool init()
  {
    using namespace cryptonote;

    if (!single_tx_test_base::init())
      return false;

    account_keys bob_keys = m_bob.get_keys();

    crypto::key_derivation recv_derivation;
    crypto::generate_key_derivation(m_tx_pub_key, bob_keys.m_view_secret_key, recv_derivation);

    crypto::derive_public_key(recv_derivation, 0, bob_keys.m_account_address.m_spend_public_key, m_in_ephemeral.pub);
    crypto::derive_secret_key(recv_derivation, 0, bob_keys.m_spend_secret_key, m_in_ephemeral.sec);

    return true;
  }

  bool test()
  {
    crypto::key_image ki;
    crypto::generate_key_image(m_in_ephemeral.pub, m_in_ephemeral.sec, ki);
    return true;
  }

private:
  cryptonote::keypair m_in_ephemeral;
};
