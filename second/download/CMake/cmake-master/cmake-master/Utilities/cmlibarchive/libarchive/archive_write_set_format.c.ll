; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i32, i32 (%struct.archive*)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, {}*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque

@codes = internal global [19 x %struct.anon] [%struct.anon { i32 917504, i32 (%struct.archive*)* @archive_write_set_format_7zip }, %struct.anon { i32 65536, i32 (%struct.archive*)* @archive_write_set_format_cpio }, %struct.anon { i32 65537, i32 (%struct.archive*)* @archive_write_set_format_cpio }, %struct.anon { i32 65540, i32 (%struct.archive*)* @archive_write_set_format_cpio_newc }, %struct.anon { i32 262144, i32 (%struct.archive*)* @archive_write_set_format_iso9660 }, %struct.anon { i32 524288, i32 (%struct.archive*)* @archive_write_set_format_mtree }, %struct.anon { i32 589824, i32 (%struct.archive*)* @archive_write_set_format_raw }, %struct.anon { i32 131072, i32 (%struct.archive*)* @archive_write_set_format_shar }, %struct.anon { i32 131073, i32 (%struct.archive*)* @archive_write_set_format_shar }, %struct.anon { i32 131074, i32 (%struct.archive*)* @archive_write_set_format_shar_dump }, %struct.anon { i32 196608, i32 (%struct.archive*)* @archive_write_set_format_pax_restricted }, %struct.anon { i32 196612, i32 (%struct.archive*)* @archive_write_set_format_gnutar }, %struct.anon { i32 196610, i32 (%struct.archive*)* @archive_write_set_format_pax }, %struct.anon { i32 196611, i32 (%struct.archive*)* @archive_write_set_format_pax_restricted }, %struct.anon { i32 196609, i32 (%struct.archive*)* @archive_write_set_format_ustar }, %struct.anon { i32 983040, i32 (%struct.archive*)* @archive_write_set_format_warc }, %struct.anon { i32 655360, i32 (%struct.archive*)* @archive_write_set_format_xar }, %struct.anon { i32 327680, i32 (%struct.archive*)* @archive_write_set_format_zip }, %struct.anon zeroinitializer], align 16
@.str = private unnamed_addr constant [15 x i8] c"No such format\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format(%struct.archive* %a, i32 %code) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %code.addr = alloca i32, align 4
  %i = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !118, metadata !119), !dbg !120
  store i32 %code, i32* %code.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %code.addr, metadata !121, metadata !119), !dbg !122
  call void @llvm.dbg.declare(metadata i32* %i, metadata !123, metadata !119), !dbg !124
  store i32 0, i32* %i, align 4, !dbg !125
  br label %for.cond, !dbg !127

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !128
  %idxprom = sext i32 %0 to i64, !dbg !131
  %arrayidx = getelementptr inbounds [19 x %struct.anon], [19 x %struct.anon]* @codes, i64 0, i64 %idxprom, !dbg !131
  %code1 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 0, !dbg !132
  %1 = load i32, i32* %code1, align 16, !dbg !132
  %cmp = icmp ne i32 %1, 0, !dbg !133
  br i1 %cmp, label %for.body, label %for.end, !dbg !134

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %code.addr, align 4, !dbg !135
  %3 = load i32, i32* %i, align 4, !dbg !138
  %idxprom2 = sext i32 %3 to i64, !dbg !139
  %arrayidx3 = getelementptr inbounds [19 x %struct.anon], [19 x %struct.anon]* @codes, i64 0, i64 %idxprom2, !dbg !139
  %code4 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx3, i32 0, i32 0, !dbg !140
  %4 = load i32, i32* %code4, align 16, !dbg !140
  %cmp5 = icmp eq i32 %2, %4, !dbg !141
  br i1 %cmp5, label %if.then, label %if.end, !dbg !142

if.then:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4, !dbg !143
  %idxprom6 = sext i32 %5 to i64, !dbg !144
  %arrayidx7 = getelementptr inbounds [19 x %struct.anon], [19 x %struct.anon]* @codes, i64 0, i64 %idxprom6, !dbg !144
  %setter = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx7, i32 0, i32 1, !dbg !145
  %6 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %setter, align 8, !dbg !145
  %7 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !146
  %call = call i32 %6(%struct.archive* %7), !dbg !147
  store i32 %call, i32* %retval, align 4, !dbg !148
  br label %return, !dbg !148

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !149

for.inc:                                          ; preds = %if.end
  %8 = load i32, i32* %i, align 4, !dbg !150
  %inc = add nsw i32 %8, 1, !dbg !150
  store i32 %inc, i32* %i, align 4, !dbg !150
  br label %for.cond, !dbg !152

for.end:                                          ; preds = %for.cond
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !153
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 22, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i32 0, i32 0)), !dbg !154
  store i32 -30, i32* %retval, align 4, !dbg !155
  br label %return, !dbg !155

return:                                           ; preds = %for.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !156
  ret i32 %10, !dbg !156
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @archive_write_set_format_7zip(%struct.archive*) #2

declare i32 @archive_write_set_format_cpio(%struct.archive*) #2

declare i32 @archive_write_set_format_cpio_newc(%struct.archive*) #2

declare i32 @archive_write_set_format_iso9660(%struct.archive*) #2

declare i32 @archive_write_set_format_mtree(%struct.archive*) #2

declare i32 @archive_write_set_format_raw(%struct.archive*) #2

declare i32 @archive_write_set_format_shar(%struct.archive*) #2

declare i32 @archive_write_set_format_shar_dump(%struct.archive*) #2

declare i32 @archive_write_set_format_pax_restricted(%struct.archive*) #2

declare i32 @archive_write_set_format_gnutar(%struct.archive*) #2

declare i32 @archive_write_set_format_pax(%struct.archive*) #2

declare i32 @archive_write_set_format_ustar(%struct.archive*) #2

declare i32 @archive_write_set_format_warc(%struct.archive*) #2

declare i32 @archive_write_set_format_xar(%struct.archive*) #2

declare i32 @archive_write_set_format_zip(%struct.archive*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!115, !116}
!llvm.ident = !{!117}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !106)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "archive_write_set_format", scope: !1, file: !1, line: 67, type: !5, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
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
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !37, line: 109, baseType: !38)
!37 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
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
!106 = !{!107}
!107 = !DIGlobalVariable(name: "codes", scope: !0, file: !1, line: 42, type: !108, isLocal: true, isDefinition: true, variable: [19 x %struct.anon]* @codes)
!108 = !DICompositeType(tag: DW_TAG_array_type, baseType: !109, size: 2432, align: 64, elements: !113)
!109 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 42, size: 128, align: 64, elements: !110)
!110 = !{!111, !112}
!111 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !109, file: !1, line: 42, baseType: !7, size: 32, align: 32)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "setter", scope: !109, file: !1, line: 42, baseType: !20, size: 64, align: 64, offset: 64)
!113 = !{!114}
!114 = !DISubrange(count: 19)
!115 = !{i32 2, !"Dwarf Version", i32 4}
!116 = !{i32 2, !"Debug Info Version", i32 3}
!117 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!118 = !DILocalVariable(name: "a", arg: 1, scope: !4, file: !1, line: 67, type: !8)
!119 = !DIExpression()
!120 = !DILocation(line: 67, column: 42, scope: !4)
!121 = !DILocalVariable(name: "code", arg: 2, scope: !4, file: !1, line: 67, type: !7)
!122 = !DILocation(line: 67, column: 49, scope: !4)
!123 = !DILocalVariable(name: "i", scope: !4, file: !1, line: 69, type: !7)
!124 = !DILocation(line: 69, column: 6, scope: !4)
!125 = !DILocation(line: 71, column: 9, scope: !126)
!126 = distinct !DILexicalBlock(scope: !4, file: !1, line: 71, column: 2)
!127 = !DILocation(line: 71, column: 7, scope: !126)
!128 = !DILocation(line: 71, column: 20, scope: !129)
!129 = !DILexicalBlockFile(scope: !130, file: !1, discriminator: 1)
!130 = distinct !DILexicalBlock(scope: !126, file: !1, line: 71, column: 2)
!131 = !DILocation(line: 71, column: 14, scope: !129)
!132 = !DILocation(line: 71, column: 23, scope: !129)
!133 = !DILocation(line: 71, column: 28, scope: !129)
!134 = !DILocation(line: 71, column: 2, scope: !129)
!135 = !DILocation(line: 72, column: 7, scope: !136)
!136 = distinct !DILexicalBlock(scope: !137, file: !1, line: 72, column: 7)
!137 = distinct !DILexicalBlock(scope: !130, file: !1, line: 71, column: 39)
!138 = !DILocation(line: 72, column: 21, scope: !136)
!139 = !DILocation(line: 72, column: 15, scope: !136)
!140 = !DILocation(line: 72, column: 24, scope: !136)
!141 = !DILocation(line: 72, column: 12, scope: !136)
!142 = !DILocation(line: 72, column: 7, scope: !137)
!143 = !DILocation(line: 73, column: 19, scope: !136)
!144 = !DILocation(line: 73, column: 13, scope: !136)
!145 = !DILocation(line: 73, column: 22, scope: !136)
!146 = !DILocation(line: 73, column: 30, scope: !136)
!147 = !DILocation(line: 73, column: 12, scope: !136)
!148 = !DILocation(line: 73, column: 4, scope: !136)
!149 = !DILocation(line: 74, column: 2, scope: !137)
!150 = !DILocation(line: 71, column: 35, scope: !151)
!151 = !DILexicalBlockFile(scope: !130, file: !1, discriminator: 2)
!152 = !DILocation(line: 71, column: 2, scope: !151)
!153 = !DILocation(line: 76, column: 20, scope: !4)
!154 = !DILocation(line: 76, column: 2, scope: !4)
!155 = !DILocation(line: 77, column: 2, scope: !4)
!156 = !DILocation(line: 78, column: 1, scope: !4)
