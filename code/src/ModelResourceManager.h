#include <string>
#include <map>
#include <vector>
#include "Resources.h"

namespace resources
{
	struct tagModel {};

    typedef Handle<tagModel>	HModel;

    class ModelResourceManager
    {
    public:
        typedef HandleMgr<model_t, HModel> HModelResourceManager;

        struct istring_less
        {
            bool operator() (const std::string& l, const std::string& r) const
            {
                return (strcmp(l.c_str(), r.c_str()) < 0);
            }
        };

        typedef std::map<std::string, HModel, istring_less>	NameIndex;
        typedef std::pair<NameIndex::iterator, bool> NameIndexInsertRc;

    private:
        HModelResourceManager mResourceManagerImpl;
        NameIndex mNameIndex;

    public:

        ModelResourceManager() {};
        ~ModelResourceManager();


        HModel    GetModel(const char* name, bool  genTanget=true);
        void DeleteModel(HModel hTexture);

        const char* GetName(HModel res) const
        {
            return (mResourceManagerImpl.Dereference(res)->name);
        }


    };
}