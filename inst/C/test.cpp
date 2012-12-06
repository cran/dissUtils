#include <iostream>
#include <string>
#include <valarray>

#include "options.hpp"

#include "generic_factory.hpp"

using namespace BNT;
using namespace BNT::Difference;

int main(void){

  /************** use for real-valued examples **************
  double X[20] = {0.360090661559167,-0.432682561784328,-2.47880511717009,-0.496580461284292,0.803606376523571,0.664712110284634,0.275855333934165,0.331284952175349,-1.82367718168844,0.0755304422339227,-0.0518994701737551,0.364592958384648,0.180999630156671,-1.32206820641878,-0.494925889544613,1.34451235231922,-0.873989444781004,0.00228922867967221,-0.295893049218487,-0.789012463943931};
  
  double Y[20] = {-0.629678773740529,2.28516670026376,0.106826197798163,-2.02594299691166,-1.08705262731565,-1.08831526794596,0.0713720028796692,-0.249669660207228,0.700158250112106,0.38713223472801,1.19975672791337,-2.22892463610851,-0.640903301847887,1.06103209801042,-0.322282138103725,0.319917731385532,-0.405315976857671,0.434624269529893,1.14940640206323,-1.99050841639828};
  */

  /**************** use for probability / density examples *******/
  double X[20] = {0.101512175779912,0.10272611404123,0.000282633769835878,0.0280848985036107,0.0985953145586632,0.00291453935687738,0.0113189457170294,0.105569110630231,0.00563442751242656,0.000894583440725471,0.0218171011342372,0.0858626020827547,0.0309910473942084,0.0914987049976606,0.0965982845939082,0.0660364318571774,0.0070359179126831,0.106847776198134,0.0158160242650084,0.0199633662536855};
  double Y[20] = {0.0784192238006865,0.0527196834882864,0.102457487766738,0.0308531085936671,0.00515714187489188,0.0692636489409622,0.0758115656379517,0.00931154070023025,0.0553228731059652,0.0778600733418158,0.0488324597226727,0.0719714016744481,0.104337710754534,0.0110239572014036,0.0122243027558127,0.00119377100518665,0.0778417340210153,0.0230568449596308,0.0614615570277612,0.0308799136263395};

  std::valarray<double> A(X, 20), B(Y, 20);

  typedef std::string key_t;
  typedef Base<double> val_t;

  typedef std::map<key_t, val_t*> options_map_t;

  options_map_t optionsMap = make_options_map<key_t, double>();

  GenericFactory<key_t, val_t> factory(optionsMap.begin(), optionsMap.end());

  std::cout << "Abar = " << A.sum() / A.size() << " Bbar = " << B.sum() / B.size() << std::endl;

  for(options_map_t::iterator it = optionsMap.begin();
      it != optionsMap.end();
      ++it){

    val_t* F = factory.Create(it->first);

    if(F && !F->NeedsInitialization()){

      std::cout << it->first << " = " << F->Diff(A,B) << std::endl;

      delete F;

      F = 0;
    }
  }

  return 0;
}