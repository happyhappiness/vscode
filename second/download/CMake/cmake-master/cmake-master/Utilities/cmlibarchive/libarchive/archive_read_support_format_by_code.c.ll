; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_by_code.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, {}*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque

@.str = private unnamed_addr constant [36 x i8] c"archive_read_support_format_by_code\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_by_code(%struct.archive* %a, i32 %format_code) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %format_code.addr = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !109, metadata !110), !dbg !111
  store i32 %format_code, i32* %format_code.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %format_code.addr, metadata !112, metadata !110), !dbg !113
  br label %do.body, !dbg !114

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !115, metadata !110), !dbg !117
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !118
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 14594245, i32 1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str, i32 0, i32 0)), !dbg !118
  store i32 %call, i32* %magic_test, align 4, !dbg !118
  %1 = load i32, i32* %magic_test, align 4, !dbg !118
  %cmp = icmp eq i32 %1, -30, !dbg !118
  br i1 %cmp, label %if.then, label %if.end, !dbg !118

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !120
  br label %return, !dbg !120

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !123

do.end:                                           ; preds = %if.end
  %2 = load i32, i32* %format_code.addr, align 4, !dbg !125
  %and = and i32 %2, 16711680, !dbg !126
  switch i32 %and, label %sw.epilog [
    i32 917504, label %sw.bb
    i32 458752, label %sw.bb2
    i32 786432, label %sw.bb4
    i32 65536, label %sw.bb6
    i32 262144, label %sw.bb8
    i32 720896, label %sw.bb10
    i32 524288, label %sw.bb12
    i32 851968, label %sw.bb14
    i32 196608, label %sw.bb16
    i32 655360, label %sw.bb18
    i32 327680, label %sw.bb20
  ], !dbg !127

sw.bb:                                            ; preds = %do.end
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !128
  %call1 = call i32 @archive_read_support_format_7zip(%struct.archive* %3), !dbg !130
  store i32 %call1, i32* %retval, align 4, !dbg !131
  br label %return, !dbg !131

sw.bb2:                                           ; preds = %do.end
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !132
  %call3 = call i32 @archive_read_support_format_ar(%struct.archive* %4), !dbg !133
  store i32 %call3, i32* %retval, align 4, !dbg !134
  br label %return, !dbg !134

sw.bb4:                                           ; preds = %do.end
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !135
  %call5 = call i32 @archive_read_support_format_cab(%struct.archive* %5), !dbg !136
  store i32 %call5, i32* %retval, align 4, !dbg !137
  br label %return, !dbg !137

sw.bb6:                                           ; preds = %do.end
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !138
  %call7 = call i32 @archive_read_support_format_cpio(%struct.archive* %6), !dbg !139
  store i32 %call7, i32* %retval, align 4, !dbg !140
  br label %return, !dbg !140

sw.bb8:                                           ; preds = %do.end
  %7 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !141
  %call9 = call i32 @archive_read_support_format_iso9660(%struct.archive* %7), !dbg !142
  store i32 %call9, i32* %retval, align 4, !dbg !143
  br label %return, !dbg !143

sw.bb10:                                          ; preds = %do.end
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !144
  %call11 = call i32 @archive_read_support_format_lha(%struct.archive* %8), !dbg !145
  store i32 %call11, i32* %retval, align 4, !dbg !146
  br label %return, !dbg !146

sw.bb12:                                          ; preds = %do.end
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !147
  %call13 = call i32 @archive_read_support_format_mtree(%struct.archive* %9), !dbg !148
  store i32 %call13, i32* %retval, align 4, !dbg !149
  br label %return, !dbg !149

sw.bb14:                                          ; preds = %do.end
  %10 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !150
  %call15 = call i32 @archive_read_support_format_rar(%struct.archive* %10), !dbg !151
  store i32 %call15, i32* %retval, align 4, !dbg !152
  br label %return, !dbg !152

sw.bb16:                                          ; preds = %do.end
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !153
  %call17 = call i32 @archive_read_support_format_tar(%struct.archive* %11), !dbg !154
  store i32 %call17, i32* %retval, align 4, !dbg !155
  br label %return, !dbg !155

sw.bb18:                                          ; preds = %do.end
  %12 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !156
  %call19 = call i32 @archive_read_support_format_xar(%struct.archive* %12), !dbg !157
  store i32 %call19, i32* %retval, align 4, !dbg !158
  br label %return, !dbg !158

sw.bb20:                                          ; preds = %do.end
  %13 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !159
  %call21 = call i32 @archive_read_support_format_zip(%struct.archive* %13), !dbg !160
  store i32 %call21, i32* %retval, align 4, !dbg !161
  br label %return, !dbg !161

sw.epilog:                                        ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !162
  br label %return, !dbg !162

return:                                           ; preds = %sw.epilog, %sw.bb20, %sw.bb18, %sw.bb16, %sw.bb14, %sw.bb12, %sw.bb10, %sw.bb8, %sw.bb6, %sw.bb4, %sw.bb2, %sw.bb, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !163
  ret i32 %14, !dbg !163
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare i32 @archive_read_support_format_7zip(%struct.archive*) #2

declare i32 @archive_read_support_format_ar(%struct.archive*) #2

declare i32 @archive_read_support_format_cab(%struct.archive*) #2

declare i32 @archive_read_support_format_cpio(%struct.archive*) #2

declare i32 @archive_read_support_format_iso9660(%struct.archive*) #2

declare i32 @archive_read_support_format_lha(%struct.archive*) #2

declare i32 @archive_read_support_format_mtree(%struct.archive*) #2

declare i32 @archive_read_support_format_rar(%struct.archive*) #2

declare i32 @archive_read_support_format_tar(%struct.archive*) #2

declare i32 @archive_read_support_format_xar(%struct.archive*) #2

declare i32 @archive_read_support_format_zip(%struct.archive*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!106, !107}
!llvm.ident = !{!108}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_by_code.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "archive_read_support_format_by_code", scope: !1, file: !1, line: 33, type: !5, isLocal: false, isDefinition: true, scopeLine: 34, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !79, !80, !81, !82, !83, !84, !85, !86, !94, !95, !96, !97, !100, !101, !102, !103, !104, !105}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !23, !24, !31, !32, !46, !52, !57, !58, !65, !66, !70, !72}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!7, !8}
!23 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !25, size: 64, align: 64, offset: 128)
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DISubroutineType(types: !27)
!27 = !{!7, !8, !28}
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !30, line: 180, flags: DIFlagFwdDecl)
!30 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!31 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !33, size: 64, align: 64, offset: 256)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!34 = !DISubroutineType(types: !35)
!35 = !{!36, !8, !41, !43}
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !37, line: 102, baseType: !38)
!37 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !39, line: 172, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !44, line: 62, baseType: !45)
!44 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !47, size: 64, align: 64, offset: 320)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DISubroutineType(types: !49)
!49 = !{!36, !8, !41, !43, !50}
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !51, line: 40, baseType: !40)
!51 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!52 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !53, size: 64, align: 64, offset: 384)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DISubroutineType(types: !55)
!55 = !{!7, !8, !56}
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !25, size: 64, align: 64, offset: 448)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !59, size: 64, align: 64, offset: 512)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!7, !8, !62, !63, !64}
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !67, size: 64, align: 64, offset: 640)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!50, !8, !7}
!70 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !71, size: 64, align: 64, offset: 704)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !73, size: 64, align: 64, offset: 768)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!76, !8, !7}
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!77 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !78)
!78 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !7, size: 32, align: 32, offset: 128)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !76, size: 64, align: 64, offset: 192)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !7, size: 32, align: 32, offset: 256)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !76, size: 64, align: 64, offset: 320)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !7, size: 32, align: 32, offset: 384)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !7, size: 32, align: 32, offset: 416)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !76, size: 64, align: 64, offset: 448)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !87, size: 192, align: 64, offset: 512)
!87 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !88, line: 58, size: 192, align: 64, elements: !89)
!88 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!89 = !{!90, !92, !93}
!90 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !87, file: !88, line: 59, baseType: !91, size: 64, align: 64)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !87, file: !88, line: 60, baseType: !43, size: 64, align: 64, offset: 64)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !87, file: !88, line: 61, baseType: !43, size: 64, align: 64, offset: 128)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !91, size: 64, align: 64, offset: 704)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !98, size: 64, align: 64, offset: 832)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !88, line: 70, flags: DIFlagFwdDecl)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !76, size: 64, align: 64, offset: 896)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !50, size: 64, align: 64, offset: 960)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !50, size: 64, align: 64, offset: 1024)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !43, size: 64, align: 64, offset: 1088)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !78, size: 8, align: 8, offset: 1152)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !43, size: 64, align: 64, offset: 1216)
!106 = !{i32 2, !"Dwarf Version", i32 4}
!107 = !{i32 2, !"Debug Info Version", i32 3}
!108 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!109 = !DILocalVariable(name: "a", arg: 1, scope: !4, file: !1, line: 33, type: !8)
!110 = !DIExpression()
!111 = !DILocation(line: 33, column: 53, scope: !4)
!112 = !DILocalVariable(name: "format_code", arg: 2, scope: !4, file: !1, line: 33, type: !7)
!113 = !DILocation(line: 33, column: 60, scope: !4)
!114 = !DILocation(line: 35, column: 2, scope: !4)
!115 = !DILocalVariable(name: "magic_test", scope: !116, file: !1, line: 35, type: !7)
!116 = distinct !DILexicalBlock(scope: !4, file: !1, line: 35, column: 2)
!117 = !DILocation(line: 35, column: 2, scope: !116)
!118 = !DILocation(line: 35, column: 2, scope: !119)
!119 = !DILexicalBlockFile(scope: !116, file: !1, discriminator: 1)
!120 = !DILocation(line: 35, column: 2, scope: !121)
!121 = !DILexicalBlockFile(scope: !122, file: !1, discriminator: 2)
!122 = distinct !DILexicalBlock(scope: !116, file: !1, line: 35, column: 2)
!123 = !DILocation(line: 35, column: 2, scope: !124)
!124 = !DILexicalBlockFile(scope: !116, file: !1, discriminator: 3)
!125 = !DILocation(line: 38, column: 10, scope: !4)
!126 = !DILocation(line: 38, column: 22, scope: !4)
!127 = !DILocation(line: 38, column: 2, scope: !4)
!128 = !DILocation(line: 40, column: 43, scope: !129)
!129 = distinct !DILexicalBlock(scope: !4, file: !1, line: 38, column: 50)
!130 = !DILocation(line: 40, column: 10, scope: !129)
!131 = !DILocation(line: 40, column: 3, scope: !129)
!132 = !DILocation(line: 43, column: 41, scope: !129)
!133 = !DILocation(line: 43, column: 10, scope: !129)
!134 = !DILocation(line: 43, column: 3, scope: !129)
!135 = !DILocation(line: 46, column: 42, scope: !129)
!136 = !DILocation(line: 46, column: 10, scope: !129)
!137 = !DILocation(line: 46, column: 3, scope: !129)
!138 = !DILocation(line: 49, column: 43, scope: !129)
!139 = !DILocation(line: 49, column: 10, scope: !129)
!140 = !DILocation(line: 49, column: 3, scope: !129)
!141 = !DILocation(line: 52, column: 46, scope: !129)
!142 = !DILocation(line: 52, column: 10, scope: !129)
!143 = !DILocation(line: 52, column: 3, scope: !129)
!144 = !DILocation(line: 55, column: 42, scope: !129)
!145 = !DILocation(line: 55, column: 10, scope: !129)
!146 = !DILocation(line: 55, column: 3, scope: !129)
!147 = !DILocation(line: 58, column: 44, scope: !129)
!148 = !DILocation(line: 58, column: 10, scope: !129)
!149 = !DILocation(line: 58, column: 3, scope: !129)
!150 = !DILocation(line: 61, column: 42, scope: !129)
!151 = !DILocation(line: 61, column: 10, scope: !129)
!152 = !DILocation(line: 61, column: 3, scope: !129)
!153 = !DILocation(line: 64, column: 42, scope: !129)
!154 = !DILocation(line: 64, column: 10, scope: !129)
!155 = !DILocation(line: 64, column: 3, scope: !129)
!156 = !DILocation(line: 67, column: 42, scope: !129)
!157 = !DILocation(line: 67, column: 10, scope: !129)
!158 = !DILocation(line: 67, column: 3, scope: !129)
!159 = !DILocation(line: 70, column: 42, scope: !129)
!160 = !DILocation(line: 70, column: 10, scope: !129)
!161 = !DILocation(line: 70, column: 3, scope: !129)
!162 = !DILocation(line: 73, column: 2, scope: !4)
!163 = !DILocation(line: 74, column: 1, scope: !4)
