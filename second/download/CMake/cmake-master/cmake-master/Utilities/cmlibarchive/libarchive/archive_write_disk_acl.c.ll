; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_disk_acl.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct.archive_acl = type { i32, %struct.archive_acl_entry*, %struct.archive_acl_entry*, i32, i32*, i8*, i32 }
%struct.archive_acl_entry = type { %struct.archive_acl_entry*, i32, i32, i32, i32, %struct.archive_mstring }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.archive_string = type { i8*, i64, i64 }

; Function Attrs: nounwind uwtable
define i32 @archive_write_disk_set_acls(%struct.archive* %a, i32 %fd, i8* %name, %struct.archive_acl* %abstract_acl) #0 !dbg !4 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %fd.addr = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %abstract_acl.addr = alloca %struct.archive_acl*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !66, metadata !67), !dbg !68
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !69, metadata !67), !dbg !70
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !71, metadata !67), !dbg !72
  store %struct.archive_acl* %abstract_acl, %struct.archive_acl** %abstract_acl.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_acl** %abstract_acl.addr, metadata !73, metadata !67), !dbg !74
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !75
  %1 = load i32, i32* %fd.addr, align 4, !dbg !76
  %2 = load i8*, i8** %name.addr, align 8, !dbg !77
  %3 = load %struct.archive_acl*, %struct.archive_acl** %abstract_acl.addr, align 8, !dbg !78
  ret i32 0, !dbg !79
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!63, !64}
!llvm.ident = !{!65}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_disk_acl.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "archive_write_disk_set_acls", scope: !1, file: !1, line: 52, type: !5, isLocal: false, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !7, !11, !14}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 179, flags: DIFlagFwdDecl)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!13 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl", file: !16, line: 46, size: 448, align: 64, elements: !17)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_acl_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!17 = !{!18, !24, !58, !59, !60, !61, !62}
!18 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !15, file: !16, line: 47, baseType: !19, size: 32, align: 32)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !20, line: 70, baseType: !21)
!20 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !22, line: 129, baseType: !23)
!22 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!23 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "acl_head", scope: !15, file: !16, line: 48, baseType: !25, size: 64, align: 64, offset: 64)
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl_entry", file: !16, line: 37, size: 1024, align: 64, elements: !27)
!27 = !{!28, !29, !30, !31, !32, !33}
!28 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !26, file: !16, line: 38, baseType: !25, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !26, file: !16, line: 39, baseType: !7, size: 32, align: 32, offset: 64)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "tag", scope: !26, file: !16, line: 40, baseType: !7, size: 32, align: 32, offset: 96)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "permset", scope: !26, file: !16, line: 41, baseType: !7, size: 32, align: 32, offset: 128)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !26, file: !16, line: 42, baseType: !7, size: 32, align: 32, offset: 160)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !26, file: !16, line: 43, baseType: !34, size: 832, align: 64, offset: 192)
!34 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !35, line: 209, size: 832, align: 64, elements: !36)
!35 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!36 = !{!37, !47, !48, !56, !57}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !34, file: !35, line: 210, baseType: !38, size: 192, align: 64)
!38 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !35, line: 58, size: 192, align: 64, elements: !39)
!39 = !{!40, !42, !46}
!40 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !38, file: !35, line: 59, baseType: !41, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !38, file: !35, line: 60, baseType: !43, size: 64, align: 64, offset: 64)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !44, line: 62, baseType: !45)
!44 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !38, file: !35, line: 61, baseType: !43, size: 64, align: 64, offset: 128)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !34, file: !35, line: 211, baseType: !38, size: 192, align: 64, offset: 192)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !34, file: !35, line: 212, baseType: !49, size: 192, align: 64, offset: 384)
!49 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !35, line: 64, size: 192, align: 64, elements: !50)
!50 = !{!51, !54, !55}
!51 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !49, file: !35, line: 65, baseType: !52, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !44, line: 90, baseType: !7)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !49, file: !35, line: 66, baseType: !43, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !49, file: !35, line: 67, baseType: !43, size: 64, align: 64, offset: 128)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !34, file: !35, line: 213, baseType: !38, size: 192, align: 64, offset: 576)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !34, file: !35, line: 218, baseType: !7, size: 32, align: 32, offset: 768)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "acl_p", scope: !15, file: !16, line: 49, baseType: !25, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "acl_state", scope: !15, file: !16, line: 50, baseType: !7, size: 32, align: 32, offset: 192)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text_w", scope: !15, file: !16, line: 51, baseType: !52, size: 64, align: 64, offset: 256)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text", scope: !15, file: !16, line: 52, baseType: !41, size: 64, align: 64, offset: 320)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "acl_types", scope: !15, file: !16, line: 53, baseType: !7, size: 32, align: 32, offset: 384)
!63 = !{i32 2, !"Dwarf Version", i32 4}
!64 = !{i32 2, !"Debug Info Version", i32 3}
!65 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!66 = !DILocalVariable(name: "a", arg: 1, scope: !4, file: !1, line: 52, type: !8)
!67 = !DIExpression()
!68 = !DILocation(line: 52, column: 45, scope: !4)
!69 = !DILocalVariable(name: "fd", arg: 2, scope: !4, file: !1, line: 52, type: !7)
!70 = !DILocation(line: 52, column: 52, scope: !4)
!71 = !DILocalVariable(name: "name", arg: 3, scope: !4, file: !1, line: 52, type: !11)
!72 = !DILocation(line: 52, column: 68, scope: !4)
!73 = !DILocalVariable(name: "abstract_acl", arg: 4, scope: !4, file: !1, line: 53, type: !14)
!74 = !DILocation(line: 53, column: 23, scope: !4)
!75 = !DILocation(line: 55, column: 8, scope: !4)
!76 = !DILocation(line: 56, column: 8, scope: !4)
!77 = !DILocation(line: 57, column: 8, scope: !4)
!78 = !DILocation(line: 58, column: 8, scope: !4)
!79 = !DILocation(line: 59, column: 2, scope: !4)
