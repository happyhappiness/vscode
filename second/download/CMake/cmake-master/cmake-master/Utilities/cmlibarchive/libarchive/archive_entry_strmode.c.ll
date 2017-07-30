; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_strmode.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_entry = type { %struct.archive*, i8*, i32, %struct.aest, i32, %struct.archive_mstring, i64, i64, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, i8, i8*, i64, %struct.archive_acl, %struct.ae_xattr*, %struct.ae_xattr*, %struct.ae_sparse*, %struct.ae_sparse*, %struct.ae_sparse*, [12 x i8] }
%struct.archive = type opaque
%struct.aest = type { i64, i32, i64, i32, i64, i32, i64, i32, i64, i64, i32, i64, i64, i32, i64, i64, i64, i32, i64, i64, i64 }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_acl = type { i32, %struct.archive_acl_entry*, %struct.archive_acl_entry*, i32, i32*, i8*, i32 }
%struct.archive_acl_entry = type { %struct.archive_acl_entry*, i32, i32, i32, i32, %struct.archive_mstring }
%struct.ae_xattr = type { %struct.ae_xattr*, i8*, i8*, i64 }
%struct.ae_sparse = type { %struct.ae_sparse*, i64, i64 }

@archive_entry_strmode.permbits = internal constant [9 x i32] [i32 256, i32 128, i32 64, i32 32, i32 16, i32 8, i32 4, i32 2, i32 1], align 16
@.str = private unnamed_addr constant [12 x i8] c"?rwxrwxrwx \00", align 1

; Function Attrs: nounwind uwtable
define i8* @archive_entry_strmode(%struct.archive_entry* %entry1) #0 !dbg !6 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %bp = alloca i8*, align 8
  %mode = alloca i32, align 4
  %i = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !147, metadata !148), !dbg !149
  call void @llvm.dbg.declare(metadata i8** %bp, metadata !150, metadata !148), !dbg !151
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !152
  %strmode = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 23, !dbg !153
  %arraydecay = getelementptr inbounds [12 x i8], [12 x i8]* %strmode, i32 0, i32 0, !dbg !152
  store i8* %arraydecay, i8** %bp, align 8, !dbg !151
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !154, metadata !148), !dbg !155
  call void @llvm.dbg.declare(metadata i32* %i, metadata !156, metadata !148), !dbg !157
  %1 = load i8*, i8** %bp, align 8, !dbg !158
  %call = call i8* @strcpy(i8* %1, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i32 0, i32 0)) #4, !dbg !159
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !160
  %call2 = call i32 @archive_entry_mode(%struct.archive_entry* %2), !dbg !161
  store i32 %call2, i32* %mode, align 4, !dbg !162
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !163
  %call3 = call i32 @archive_entry_filetype(%struct.archive_entry* %3), !dbg !164
  switch i32 %call3, label %sw.default [
    i32 32768, label %sw.bb
    i32 24576, label %sw.bb4
    i32 8192, label %sw.bb6
    i32 16384, label %sw.bb8
    i32 40960, label %sw.bb10
    i32 49152, label %sw.bb12
    i32 4096, label %sw.bb14
  ], !dbg !165

sw.bb:                                            ; preds = %entry
  %4 = load i8*, i8** %bp, align 8, !dbg !166
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 0, !dbg !166
  store i8 45, i8* %arrayidx, align 1, !dbg !168
  br label %sw.epilog, !dbg !169

sw.bb4:                                           ; preds = %entry
  %5 = load i8*, i8** %bp, align 8, !dbg !170
  %arrayidx5 = getelementptr inbounds i8, i8* %5, i64 0, !dbg !170
  store i8 98, i8* %arrayidx5, align 1, !dbg !171
  br label %sw.epilog, !dbg !172

sw.bb6:                                           ; preds = %entry
  %6 = load i8*, i8** %bp, align 8, !dbg !173
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 0, !dbg !173
  store i8 99, i8* %arrayidx7, align 1, !dbg !174
  br label %sw.epilog, !dbg !175

sw.bb8:                                           ; preds = %entry
  %7 = load i8*, i8** %bp, align 8, !dbg !176
  %arrayidx9 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !176
  store i8 100, i8* %arrayidx9, align 1, !dbg !177
  br label %sw.epilog, !dbg !178

sw.bb10:                                          ; preds = %entry
  %8 = load i8*, i8** %bp, align 8, !dbg !179
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 0, !dbg !179
  store i8 108, i8* %arrayidx11, align 1, !dbg !180
  br label %sw.epilog, !dbg !181

sw.bb12:                                          ; preds = %entry
  %9 = load i8*, i8** %bp, align 8, !dbg !182
  %arrayidx13 = getelementptr inbounds i8, i8* %9, i64 0, !dbg !182
  store i8 115, i8* %arrayidx13, align 1, !dbg !183
  br label %sw.epilog, !dbg !184

sw.bb14:                                          ; preds = %entry
  %10 = load i8*, i8** %bp, align 8, !dbg !185
  %arrayidx15 = getelementptr inbounds i8, i8* %10, i64 0, !dbg !185
  store i8 112, i8* %arrayidx15, align 1, !dbg !186
  br label %sw.epilog, !dbg !187

sw.default:                                       ; preds = %entry
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !188
  %call16 = call i8* @archive_entry_hardlink(%struct.archive_entry* %11), !dbg !190
  %cmp = icmp ne i8* %call16, null, !dbg !191
  br i1 %cmp, label %if.then, label %if.end, !dbg !192

if.then:                                          ; preds = %sw.default
  %12 = load i8*, i8** %bp, align 8, !dbg !193
  %arrayidx17 = getelementptr inbounds i8, i8* %12, i64 0, !dbg !193
  store i8 104, i8* %arrayidx17, align 1, !dbg !195
  br label %sw.epilog, !dbg !196

if.end:                                           ; preds = %sw.default
  br label %sw.epilog, !dbg !197

sw.epilog:                                        ; preds = %if.end, %if.then, %sw.bb14, %sw.bb12, %sw.bb10, %sw.bb8, %sw.bb6, %sw.bb4, %sw.bb
  store i32 0, i32* %i, align 4, !dbg !198
  br label %for.cond, !dbg !200

for.cond:                                         ; preds = %for.inc, %sw.epilog
  %13 = load i32, i32* %i, align 4, !dbg !201
  %cmp18 = icmp slt i32 %13, 9, !dbg !204
  br i1 %cmp18, label %for.body, label %for.end, !dbg !205

for.body:                                         ; preds = %for.cond
  %14 = load i32, i32* %mode, align 4, !dbg !206
  %15 = load i32, i32* %i, align 4, !dbg !208
  %idxprom = sext i32 %15 to i64, !dbg !209
  %arrayidx19 = getelementptr inbounds [9 x i32], [9 x i32]* @archive_entry_strmode.permbits, i64 0, i64 %idxprom, !dbg !209
  %16 = load i32, i32* %arrayidx19, align 4, !dbg !209
  %and = and i32 %14, %16, !dbg !210
  %tobool = icmp ne i32 %and, 0, !dbg !210
  br i1 %tobool, label %if.end23, label %if.then20, !dbg !211

if.then20:                                        ; preds = %for.body
  %17 = load i32, i32* %i, align 4, !dbg !212
  %add = add nsw i32 %17, 1, !dbg !213
  %idxprom21 = sext i32 %add to i64, !dbg !214
  %18 = load i8*, i8** %bp, align 8, !dbg !214
  %arrayidx22 = getelementptr inbounds i8, i8* %18, i64 %idxprom21, !dbg !214
  store i8 45, i8* %arrayidx22, align 1, !dbg !215
  br label %if.end23, !dbg !214

if.end23:                                         ; preds = %if.then20, %for.body
  br label %for.inc, !dbg !216

for.inc:                                          ; preds = %if.end23
  %19 = load i32, i32* %i, align 4, !dbg !218
  %inc = add nsw i32 %19, 1, !dbg !218
  store i32 %inc, i32* %i, align 4, !dbg !218
  br label %for.cond, !dbg !220

for.end:                                          ; preds = %for.cond
  %20 = load i32, i32* %mode, align 4, !dbg !221
  %and24 = and i32 %20, 2048, !dbg !223
  %tobool25 = icmp ne i32 %and24, 0, !dbg !223
  br i1 %tobool25, label %if.then26, label %if.end33, !dbg !224

if.then26:                                        ; preds = %for.end
  %21 = load i32, i32* %mode, align 4, !dbg !225
  %and27 = and i32 %21, 64, !dbg !228
  %tobool28 = icmp ne i32 %and27, 0, !dbg !228
  br i1 %tobool28, label %if.then29, label %if.else, !dbg !229

if.then29:                                        ; preds = %if.then26
  %22 = load i8*, i8** %bp, align 8, !dbg !230
  %arrayidx30 = getelementptr inbounds i8, i8* %22, i64 3, !dbg !230
  store i8 115, i8* %arrayidx30, align 1, !dbg !232
  br label %if.end32, !dbg !230

if.else:                                          ; preds = %if.then26
  %23 = load i8*, i8** %bp, align 8, !dbg !233
  %arrayidx31 = getelementptr inbounds i8, i8* %23, i64 3, !dbg !233
  store i8 83, i8* %arrayidx31, align 1, !dbg !234
  br label %if.end32

if.end32:                                         ; preds = %if.else, %if.then29
  br label %if.end33, !dbg !235

if.end33:                                         ; preds = %if.end32, %for.end
  %24 = load i32, i32* %mode, align 4, !dbg !236
  %and34 = and i32 %24, 1024, !dbg !238
  %tobool35 = icmp ne i32 %and34, 0, !dbg !238
  br i1 %tobool35, label %if.then36, label %if.end44, !dbg !239

if.then36:                                        ; preds = %if.end33
  %25 = load i32, i32* %mode, align 4, !dbg !240
  %and37 = and i32 %25, 8, !dbg !243
  %tobool38 = icmp ne i32 %and37, 0, !dbg !243
  br i1 %tobool38, label %if.then39, label %if.else41, !dbg !244

if.then39:                                        ; preds = %if.then36
  %26 = load i8*, i8** %bp, align 8, !dbg !245
  %arrayidx40 = getelementptr inbounds i8, i8* %26, i64 6, !dbg !245
  store i8 115, i8* %arrayidx40, align 1, !dbg !247
  br label %if.end43, !dbg !245

if.else41:                                        ; preds = %if.then36
  %27 = load i8*, i8** %bp, align 8, !dbg !248
  %arrayidx42 = getelementptr inbounds i8, i8* %27, i64 6, !dbg !248
  store i8 83, i8* %arrayidx42, align 1, !dbg !249
  br label %if.end43

if.end43:                                         ; preds = %if.else41, %if.then39
  br label %if.end44, !dbg !250

if.end44:                                         ; preds = %if.end43, %if.end33
  %28 = load i32, i32* %mode, align 4, !dbg !251
  %and45 = and i32 %28, 512, !dbg !253
  %tobool46 = icmp ne i32 %and45, 0, !dbg !253
  br i1 %tobool46, label %if.then47, label %if.end55, !dbg !254

if.then47:                                        ; preds = %if.end44
  %29 = load i32, i32* %mode, align 4, !dbg !255
  %and48 = and i32 %29, 1, !dbg !258
  %tobool49 = icmp ne i32 %and48, 0, !dbg !258
  br i1 %tobool49, label %if.then50, label %if.else52, !dbg !259

if.then50:                                        ; preds = %if.then47
  %30 = load i8*, i8** %bp, align 8, !dbg !260
  %arrayidx51 = getelementptr inbounds i8, i8* %30, i64 9, !dbg !260
  store i8 116, i8* %arrayidx51, align 1, !dbg !262
  br label %if.end54, !dbg !260

if.else52:                                        ; preds = %if.then47
  %31 = load i8*, i8** %bp, align 8, !dbg !263
  %arrayidx53 = getelementptr inbounds i8, i8* %31, i64 9, !dbg !263
  store i8 84, i8* %arrayidx53, align 1, !dbg !264
  br label %if.end54

if.end54:                                         ; preds = %if.else52, %if.then50
  br label %if.end55, !dbg !265

if.end55:                                         ; preds = %if.end54, %if.end44
  %32 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !266
  %call56 = call i32 @archive_entry_acl_types(%struct.archive_entry* %32), !dbg !268
  %cmp57 = icmp ne i32 %call56, 0, !dbg !269
  br i1 %cmp57, label %if.then58, label %if.end60, !dbg !270

if.then58:                                        ; preds = %if.end55
  %33 = load i8*, i8** %bp, align 8, !dbg !271
  %arrayidx59 = getelementptr inbounds i8, i8* %33, i64 10, !dbg !271
  store i8 43, i8* %arrayidx59, align 1, !dbg !272
  br label %if.end60, !dbg !271

if.end60:                                         ; preds = %if.then58, %if.end55
  %34 = load i8*, i8** %bp, align 8, !dbg !273
  ret i8* %34, !dbg !274
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #2

declare i32 @archive_entry_mode(%struct.archive_entry*) #3

declare i32 @archive_entry_filetype(%struct.archive_entry*) #3

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #3

declare i32 @archive_entry_acl_types(%struct.archive_entry*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!144, !145}
!llvm.ident = !{!146}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5, globals: !138)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_strmode.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6}
!6 = distinct !DISubprogram(name: "archive_entry_strmode", scope: !1, file: !1, line: 40, type: !7, isLocal: false, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !12}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!11 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !14, line: 73, size: 8640, align: 64, elements: !15)
!14 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!15 = !{!16, !20, !21, !23, !58, !59, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !116, !124, !125, !132, !133, !134}
!16 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !13, file: !14, line: 74, baseType: !17, size: 64, align: 64)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !19, line: 152, flags: DIFlagFwdDecl)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!20 = !DIDerivedType(tag: DW_TAG_member, name: "stat", scope: !13, file: !14, line: 96, baseType: !4, size: 64, align: 64, offset: 64)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "stat_valid", scope: !13, file: !14, line: 97, baseType: !22, size: 32, align: 32, offset: 128)
!22 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "ae_stat", scope: !13, file: !14, line: 129, baseType: !24, size: 1344, align: 64, offset: 192)
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "aest", file: !14, line: 99, size: 1344, align: 64, elements: !25)
!25 = !{!26, !30, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !45, !46, !47, !52, !53, !54, !55, !56, !57}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime", scope: !24, file: !14, line: 100, baseType: !27, size: 64, align: 64)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !28, line: 40, baseType: !29)
!28 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!29 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime_nsec", scope: !24, file: !14, line: 101, baseType: !31, size: 32, align: 32, offset: 64)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !28, line: 51, baseType: !32)
!32 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime", scope: !24, file: !14, line: 102, baseType: !27, size: 64, align: 64, offset: 128)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime_nsec", scope: !24, file: !14, line: 103, baseType: !31, size: 32, align: 32, offset: 192)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime", scope: !24, file: !14, line: 104, baseType: !27, size: 64, align: 64, offset: 256)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime_nsec", scope: !24, file: !14, line: 105, baseType: !31, size: 32, align: 32, offset: 320)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime", scope: !24, file: !14, line: 106, baseType: !27, size: 64, align: 64, offset: 384)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime_nsec", scope: !24, file: !14, line: 107, baseType: !31, size: 32, align: 32, offset: 448)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "aest_gid", scope: !24, file: !14, line: 108, baseType: !27, size: 64, align: 64, offset: 512)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ino", scope: !24, file: !14, line: 109, baseType: !27, size: 64, align: 64, offset: 576)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "aest_nlink", scope: !24, file: !14, line: 110, baseType: !31, size: 32, align: 32, offset: 640)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "aest_size", scope: !24, file: !14, line: 111, baseType: !43, size: 64, align: 64, offset: 704)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !28, line: 55, baseType: !44)
!44 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "aest_uid", scope: !24, file: !14, line: 112, baseType: !27, size: 64, align: 64, offset: 768)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev_is_broken_down", scope: !24, file: !14, line: 121, baseType: !22, size: 32, align: 32, offset: 832)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev", scope: !24, file: !14, line: 122, baseType: !48, size: 64, align: 64, offset: 896)
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !49, line: 44, baseType: !50)
!49 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !51, line: 124, baseType: !44)
!51 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!52 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devmajor", scope: !24, file: !14, line: 123, baseType: !48, size: 64, align: 64, offset: 960)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devminor", scope: !24, file: !14, line: 124, baseType: !48, size: 64, align: 64, offset: 1024)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev_is_broken_down", scope: !24, file: !14, line: 125, baseType: !22, size: 32, align: 32, offset: 1088)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev", scope: !24, file: !14, line: 126, baseType: !48, size: 64, align: 64, offset: 1152)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevmajor", scope: !24, file: !14, line: 127, baseType: !48, size: 64, align: 64, offset: 1216)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevminor", scope: !24, file: !14, line: 128, baseType: !48, size: 64, align: 64, offset: 1280)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "ae_set", scope: !13, file: !14, line: 131, baseType: !22, size: 32, align: 32, offset: 1536)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_text", scope: !13, file: !14, line: 145, baseType: !60, size: 832, align: 64, offset: 1600)
!60 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !61, line: 209, size: 832, align: 64, elements: !62)
!61 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!62 = !{!63, !72, !73, !81, !82}
!63 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !60, file: !61, line: 210, baseType: !64, size: 192, align: 64)
!64 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !61, line: 58, size: 192, align: 64, elements: !65)
!65 = !{!66, !68, !71}
!66 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !64, file: !61, line: 59, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !64, file: !61, line: 60, baseType: !69, size: 64, align: 64, offset: 64)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !70, line: 62, baseType: !44)
!70 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!71 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !64, file: !61, line: 61, baseType: !69, size: 64, align: 64, offset: 128)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !60, file: !61, line: 211, baseType: !64, size: 192, align: 64, offset: 192)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !60, file: !61, line: 212, baseType: !74, size: 192, align: 64, offset: 384)
!74 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !61, line: 64, size: 192, align: 64, elements: !75)
!75 = !{!76, !79, !80}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !74, file: !61, line: 65, baseType: !77, size: 64, align: 64)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !70, line: 90, baseType: !22)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !74, file: !61, line: 66, baseType: !69, size: 64, align: 64, offset: 64)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !74, file: !61, line: 67, baseType: !69, size: 64, align: 64, offset: 128)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !60, file: !61, line: 213, baseType: !64, size: 192, align: 64, offset: 576)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !60, file: !61, line: 218, baseType: !22, size: 32, align: 32, offset: 768)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_set", scope: !13, file: !14, line: 146, baseType: !44, size: 64, align: 64, offset: 2432)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_clear", scope: !13, file: !14, line: 147, baseType: !44, size: 64, align: 64, offset: 2496)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "ae_gname", scope: !13, file: !14, line: 148, baseType: !60, size: 832, align: 64, offset: 2560)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "ae_hardlink", scope: !13, file: !14, line: 149, baseType: !60, size: 832, align: 64, offset: 3392)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "ae_pathname", scope: !13, file: !14, line: 150, baseType: !60, size: 832, align: 64, offset: 4224)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "ae_symlink", scope: !13, file: !14, line: 151, baseType: !60, size: 832, align: 64, offset: 5056)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "ae_uname", scope: !13, file: !14, line: 152, baseType: !60, size: 832, align: 64, offset: 5888)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "ae_sourcepath", scope: !13, file: !14, line: 155, baseType: !60, size: 832, align: 64, offset: 6720)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "encryption", scope: !13, file: !14, line: 160, baseType: !11, size: 8, align: 8, offset: 7552)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata", scope: !13, file: !14, line: 162, baseType: !4, size: 64, align: 64, offset: 7616)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata_size", scope: !13, file: !14, line: 163, baseType: !69, size: 64, align: 64, offset: 7680)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "acl", scope: !13, file: !14, line: 166, baseType: !95, size: 448, align: 64, offset: 7744)
!95 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl", file: !96, line: 46, size: 448, align: 64, elements: !97)
!96 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_acl_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!97 = !{!98, !101, !111, !112, !113, !114, !115}
!98 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !95, file: !96, line: 47, baseType: !99, size: 32, align: 32)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !49, line: 63, baseType: !100)
!100 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !51, line: 129, baseType: !32)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "acl_head", scope: !95, file: !96, line: 48, baseType: !102, size: 64, align: 64, offset: 64)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl_entry", file: !96, line: 37, size: 1024, align: 64, elements: !104)
!104 = !{!105, !106, !107, !108, !109, !110}
!105 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !103, file: !96, line: 38, baseType: !102, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !103, file: !96, line: 39, baseType: !22, size: 32, align: 32, offset: 64)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "tag", scope: !103, file: !96, line: 40, baseType: !22, size: 32, align: 32, offset: 96)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "permset", scope: !103, file: !96, line: 41, baseType: !22, size: 32, align: 32, offset: 128)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !103, file: !96, line: 42, baseType: !22, size: 32, align: 32, offset: 160)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !103, file: !96, line: 43, baseType: !60, size: 832, align: 64, offset: 192)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "acl_p", scope: !95, file: !96, line: 49, baseType: !102, size: 64, align: 64, offset: 128)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "acl_state", scope: !95, file: !96, line: 50, baseType: !22, size: 32, align: 32, offset: 192)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text_w", scope: !95, file: !96, line: 51, baseType: !77, size: 64, align: 64, offset: 256)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text", scope: !95, file: !96, line: 52, baseType: !67, size: 64, align: 64, offset: 320)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "acl_types", scope: !95, file: !96, line: 53, baseType: !22, size: 32, align: 32, offset: 384)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_head", scope: !13, file: !14, line: 169, baseType: !117, size: 64, align: 64, offset: 8192)
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64, align: 64)
!118 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_xattr", file: !14, line: 38, size: 256, align: 64, elements: !119)
!119 = !{!120, !121, !122, !123}
!120 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !118, file: !14, line: 39, baseType: !117, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !118, file: !14, line: 41, baseType: !67, size: 64, align: 64, offset: 64)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !118, file: !14, line: 42, baseType: !4, size: 64, align: 64, offset: 128)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !118, file: !14, line: 43, baseType: !69, size: 64, align: 64, offset: 192)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_p", scope: !13, file: !14, line: 170, baseType: !117, size: 64, align: 64, offset: 8256)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_head", scope: !13, file: !14, line: 173, baseType: !126, size: 64, align: 64, offset: 8320)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_sparse", file: !14, line: 46, size: 192, align: 64, elements: !128)
!128 = !{!129, !130, !131}
!129 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !127, file: !14, line: 47, baseType: !126, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !127, file: !14, line: 49, baseType: !27, size: 64, align: 64, offset: 64)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !127, file: !14, line: 50, baseType: !27, size: 64, align: 64, offset: 128)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_tail", scope: !13, file: !14, line: 174, baseType: !126, size: 64, align: 64, offset: 8384)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_p", scope: !13, file: !14, line: 175, baseType: !126, size: 64, align: 64, offset: 8448)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "strmode", scope: !13, file: !14, line: 178, baseType: !135, size: 96, align: 8, offset: 8512)
!135 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 96, align: 8, elements: !136)
!136 = !{!137}
!137 = !DISubrange(count: 12)
!138 = !{!139}
!139 = !DIGlobalVariable(name: "permbits", scope: !6, file: !1, line: 42, type: !140, isLocal: true, isDefinition: true, variable: [9 x i32]* @archive_entry_strmode.permbits)
!140 = !DICompositeType(tag: DW_TAG_array_type, baseType: !141, size: 288, align: 32, elements: !142)
!141 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !99)
!142 = !{!143}
!143 = !DISubrange(count: 9)
!144 = !{i32 2, !"Dwarf Version", i32 4}
!145 = !{i32 2, !"Debug Info Version", i32 3}
!146 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!147 = !DILocalVariable(name: "entry", arg: 1, scope: !6, file: !1, line: 40, type: !12)
!148 = !DIExpression()
!149 = !DILocation(line: 40, column: 45, scope: !6)
!150 = !DILocalVariable(name: "bp", scope: !6, file: !1, line: 44, type: !67)
!151 = !DILocation(line: 44, column: 8, scope: !6)
!152 = !DILocation(line: 44, column: 13, scope: !6)
!153 = !DILocation(line: 44, column: 20, scope: !6)
!154 = !DILocalVariable(name: "mode", scope: !6, file: !1, line: 45, type: !99)
!155 = !DILocation(line: 45, column: 9, scope: !6)
!156 = !DILocalVariable(name: "i", scope: !6, file: !1, line: 46, type: !22)
!157 = !DILocation(line: 46, column: 6, scope: !6)
!158 = !DILocation(line: 49, column: 9, scope: !6)
!159 = !DILocation(line: 49, column: 2, scope: !6)
!160 = !DILocation(line: 51, column: 28, scope: !6)
!161 = !DILocation(line: 51, column: 9, scope: !6)
!162 = !DILocation(line: 51, column: 7, scope: !6)
!163 = !DILocation(line: 52, column: 33, scope: !6)
!164 = !DILocation(line: 52, column: 10, scope: !6)
!165 = !DILocation(line: 52, column: 2, scope: !6)
!166 = !DILocation(line: 53, column: 18, scope: !167)
!167 = distinct !DILexicalBlock(scope: !6, file: !1, line: 52, column: 41)
!168 = !DILocation(line: 53, column: 24, scope: !167)
!169 = !DILocation(line: 53, column: 31, scope: !167)
!170 = !DILocation(line: 54, column: 18, scope: !167)
!171 = !DILocation(line: 54, column: 24, scope: !167)
!172 = !DILocation(line: 54, column: 31, scope: !167)
!173 = !DILocation(line: 55, column: 18, scope: !167)
!174 = !DILocation(line: 55, column: 24, scope: !167)
!175 = !DILocation(line: 55, column: 31, scope: !167)
!176 = !DILocation(line: 56, column: 18, scope: !167)
!177 = !DILocation(line: 56, column: 24, scope: !167)
!178 = !DILocation(line: 56, column: 31, scope: !167)
!179 = !DILocation(line: 57, column: 18, scope: !167)
!180 = !DILocation(line: 57, column: 24, scope: !167)
!181 = !DILocation(line: 57, column: 31, scope: !167)
!182 = !DILocation(line: 58, column: 18, scope: !167)
!183 = !DILocation(line: 58, column: 24, scope: !167)
!184 = !DILocation(line: 58, column: 31, scope: !167)
!185 = !DILocation(line: 59, column: 18, scope: !167)
!186 = !DILocation(line: 59, column: 24, scope: !167)
!187 = !DILocation(line: 59, column: 31, scope: !167)
!188 = !DILocation(line: 61, column: 30, scope: !189)
!189 = distinct !DILexicalBlock(scope: !167, file: !1, line: 61, column: 7)
!190 = !DILocation(line: 61, column: 7, scope: !189)
!191 = !DILocation(line: 61, column: 37, scope: !189)
!192 = !DILocation(line: 61, column: 7, scope: !167)
!193 = !DILocation(line: 62, column: 4, scope: !194)
!194 = distinct !DILexicalBlock(scope: !189, file: !1, line: 61, column: 46)
!195 = !DILocation(line: 62, column: 10, scope: !194)
!196 = !DILocation(line: 63, column: 4, scope: !194)
!197 = !DILocation(line: 65, column: 2, scope: !167)
!198 = !DILocation(line: 67, column: 9, scope: !199)
!199 = distinct !DILexicalBlock(scope: !6, file: !1, line: 67, column: 2)
!200 = !DILocation(line: 67, column: 7, scope: !199)
!201 = !DILocation(line: 67, column: 14, scope: !202)
!202 = !DILexicalBlockFile(scope: !203, file: !1, discriminator: 1)
!203 = distinct !DILexicalBlock(scope: !199, file: !1, line: 67, column: 2)
!204 = !DILocation(line: 67, column: 16, scope: !202)
!205 = !DILocation(line: 67, column: 2, scope: !202)
!206 = !DILocation(line: 68, column: 9, scope: !207)
!207 = distinct !DILexicalBlock(scope: !203, file: !1, line: 68, column: 7)
!208 = !DILocation(line: 68, column: 25, scope: !207)
!209 = !DILocation(line: 68, column: 16, scope: !207)
!210 = !DILocation(line: 68, column: 14, scope: !207)
!211 = !DILocation(line: 68, column: 7, scope: !203)
!212 = !DILocation(line: 69, column: 7, scope: !207)
!213 = !DILocation(line: 69, column: 8, scope: !207)
!214 = !DILocation(line: 69, column: 4, scope: !207)
!215 = !DILocation(line: 69, column: 12, scope: !207)
!216 = !DILocation(line: 68, column: 27, scope: !217)
!217 = !DILexicalBlockFile(scope: !207, file: !1, discriminator: 1)
!218 = !DILocation(line: 67, column: 22, scope: !219)
!219 = !DILexicalBlockFile(scope: !203, file: !1, discriminator: 2)
!220 = !DILocation(line: 67, column: 2, scope: !219)
!221 = !DILocation(line: 71, column: 6, scope: !222)
!222 = distinct !DILexicalBlock(scope: !6, file: !1, line: 71, column: 6)
!223 = !DILocation(line: 71, column: 11, scope: !222)
!224 = !DILocation(line: 71, column: 6, scope: !6)
!225 = !DILocation(line: 72, column: 7, scope: !226)
!226 = distinct !DILexicalBlock(scope: !227, file: !1, line: 72, column: 7)
!227 = distinct !DILexicalBlock(scope: !222, file: !1, line: 71, column: 22)
!228 = !DILocation(line: 72, column: 12, scope: !226)
!229 = !DILocation(line: 72, column: 7, scope: !227)
!230 = !DILocation(line: 72, column: 20, scope: !231)
!231 = !DILexicalBlockFile(scope: !226, file: !1, discriminator: 1)
!232 = !DILocation(line: 72, column: 26, scope: !231)
!233 = !DILocation(line: 73, column: 8, scope: !226)
!234 = !DILocation(line: 73, column: 14, scope: !226)
!235 = !DILocation(line: 74, column: 2, scope: !227)
!236 = !DILocation(line: 75, column: 6, scope: !237)
!237 = distinct !DILexicalBlock(scope: !6, file: !1, line: 75, column: 6)
!238 = !DILocation(line: 75, column: 11, scope: !237)
!239 = !DILocation(line: 75, column: 6, scope: !6)
!240 = !DILocation(line: 76, column: 7, scope: !241)
!241 = distinct !DILexicalBlock(scope: !242, file: !1, line: 76, column: 7)
!242 = distinct !DILexicalBlock(scope: !237, file: !1, line: 75, column: 22)
!243 = !DILocation(line: 76, column: 12, scope: !241)
!244 = !DILocation(line: 76, column: 7, scope: !242)
!245 = !DILocation(line: 76, column: 20, scope: !246)
!246 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 1)
!247 = !DILocation(line: 76, column: 26, scope: !246)
!248 = !DILocation(line: 77, column: 8, scope: !241)
!249 = !DILocation(line: 77, column: 14, scope: !241)
!250 = !DILocation(line: 78, column: 2, scope: !242)
!251 = !DILocation(line: 79, column: 6, scope: !252)
!252 = distinct !DILexicalBlock(scope: !6, file: !1, line: 79, column: 6)
!253 = !DILocation(line: 79, column: 11, scope: !252)
!254 = !DILocation(line: 79, column: 6, scope: !6)
!255 = !DILocation(line: 80, column: 7, scope: !256)
!256 = distinct !DILexicalBlock(scope: !257, file: !1, line: 80, column: 7)
!257 = distinct !DILexicalBlock(scope: !252, file: !1, line: 79, column: 22)
!258 = !DILocation(line: 80, column: 12, scope: !256)
!259 = !DILocation(line: 80, column: 7, scope: !257)
!260 = !DILocation(line: 80, column: 20, scope: !261)
!261 = !DILexicalBlockFile(scope: !256, file: !1, discriminator: 1)
!262 = !DILocation(line: 80, column: 26, scope: !261)
!263 = !DILocation(line: 81, column: 8, scope: !256)
!264 = !DILocation(line: 81, column: 14, scope: !256)
!265 = !DILocation(line: 82, column: 2, scope: !257)
!266 = !DILocation(line: 83, column: 30, scope: !267)
!267 = distinct !DILexicalBlock(scope: !6, file: !1, line: 83, column: 6)
!268 = !DILocation(line: 83, column: 6, scope: !267)
!269 = !DILocation(line: 83, column: 37, scope: !267)
!270 = !DILocation(line: 83, column: 6, scope: !6)
!271 = !DILocation(line: 84, column: 3, scope: !267)
!272 = !DILocation(line: 84, column: 10, scope: !267)
!273 = !DILocation(line: 86, column: 10, scope: !6)
!274 = !DILocation(line: 86, column: 2, scope: !6)
