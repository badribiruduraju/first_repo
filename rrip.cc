std::map<CACHE*,std::vector<uint8_t>> rripb;

void CACHE::initialize_replacement() {
  rripb[this] = std::vector<uint8_t>(NUM_SET * NUM_WAY);
  for (int i=0; i < NUM_SET * NUM_WAY; i++) {
    rripb[this][i] = 0;
  }
}

// find replacement victim
uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
  int noz = 0;
  for (uint32_t i=0; i < NUM_WAY; i++) {
    if (rripb[this][set * NUM_WAY + i] == 0) {
      noz++;
    }
  }
  if(noz == 0){
    uint min = 8;
    for (uint i=0; i < NUM_WAY; i++) {
        if(min > rripb[this][set * NUM_WAY + i]){
            min = rripb[this][set * NUM_WAY + i];
        }
    }
    for (uint i=0; i < NUM_WAY; i++) {
        rripb[this][set * NUM_WAY + i] -= min;
    }
    for (uint32_t i=0; i < NUM_WAY; i++) {
        if (rripb[this][set * NUM_WAY + i] == 0) {
            noz++;
        }
    }
  }

  int ran = (rand()%(noz))+1;
  int i{-1};
  while(ran != 0){
    i++;
    if (rripb[this][set * NUM_WAY + i] == 0) {
        ran--;
    }
  }
  return i;
  assert(false);
}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type,
                                     uint8_t hit)
{
  if (hit && type == WRITEBACK)  {
    return;
  }

  if(hit){
    rripb[this][set * NUM_WAY + way] = 7;
  }
  else{
    rripb[this][set * NUM_WAY + way] = 1;
  }
}

void CACHE::replacement_final_stats() {}
