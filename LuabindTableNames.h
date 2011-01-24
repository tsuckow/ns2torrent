

#define CreateString(str) #str

#define MakeUniqueString(str) CreateString(str##"2cbdb1bc-bebd-489e-876a-6f16d25631f8")

#define __luabind_class MakeUniqueString(__luabind_class)

#define __luabind_classes MakeUniqueString(__luabind_classes)

#define __luabind_classrep MakeUniqueString(__luabind_classrep)

#define __luabind_class_map MakeUniqueString(__luabind_class_map)

#define __luabind_class_id_map MakeUniqueString(__luabind_class_id_map)

#define __luabind_cast_graph MakeUniqueString(__luabind_cast_graph)

#define String_class MakeUniqueString(class)

#define String_property MakeUniqueString(property)

#define String_super MakeUniqueString(super)

