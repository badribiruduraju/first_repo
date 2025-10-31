std::map<CACHE*,std::map<uint16_t,uint8_t>> pcCounter;

void CACHE::initialize_replacement() {
  // pcCount[this] = std::vector<uint16_t>(NUM_SET * NUM_WAY);
  // for (int i=0; i < NUM_SET * NUM_WAY; i++) 
  //   pcCount[this][i] = 0;
  // }
  for(int i{}; i<65536; i++){
    pcCounter[this][i] = 0;
  }
}

// find replacement victim
uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
  int min = 255;
  int minind = 0;
  for (uint32_t i=0; i < NUM_WAY; i++) {
    if (pcCounter[this][this->block[set * NUM_WAY + i].ip%65535] < min) {
      min = pcCounter[this][this->block[set * NUM_WAY + i].ip%65535];
      minind = i;
    }
  }
  return minind;
  assert(false);
}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type,
                                     uint8_t hit)
{
  if (hit && type == WRITEBACK)  {
    return;
  }

  // uint32_t currVal = pcCount[this][set * NUM_WAY + way];
  if(hit){
    if(pcCounter[this][this->block[set * NUM_WAY + way].ip%65535] < 255){
      pcCounter[this][this->block[set * NUM_WAY + way].ip%65535]++;
    }
  }
  else{
    if(pcCounter[this][this->block[set * NUM_WAY + way].ip%65535] > 0){
      pcCounter[this][this->block[set * NUM_WAY + way].ip%65535]--;
    }
  }
  // for (uint32_t i=0; i < NUM_WAY; i++) {
  //   if (currVal < pcCount[this][set * NUM_WAY + i]) {
  //     pcCount[this][set * NUM_WAY + i]--;
  //   }
  // }
  // pcCount[this][set * NUM_WAY + way] = NUM_WAY - 1;
}

void CACHE::replacement_final_stats() {}
