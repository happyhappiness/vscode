; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/vauth/vauth.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [9 x i8] c"%s/%s@%s\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"%s/%s\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"%s@%s\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"\5C/@\00", align 1

; Function Attrs: nounwind uwtable
define i8* @Curl_auth_build_spn(i8* %service, i8* %host, i8* %realm) #0 !dbg !6 {
entry:
  %service.addr = alloca i8*, align 8
  %host.addr = alloca i8*, align 8
  %realm.addr = alloca i8*, align 8
  %spn = alloca i8*, align 8
  store i8* %service, i8** %service.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %service.addr, metadata !20, metadata !21), !dbg !22
  store i8* %host, i8** %host.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %host.addr, metadata !23, metadata !21), !dbg !24
  store i8* %realm, i8** %realm.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %realm.addr, metadata !25, metadata !21), !dbg !26
  call void @llvm.dbg.declare(metadata i8** %spn, metadata !27, metadata !21), !dbg !28
  store i8* null, i8** %spn, align 8, !dbg !28
  %0 = load i8*, i8** %host.addr, align 8, !dbg !29
  %tobool = icmp ne i8* %0, null, !dbg !29
  br i1 %tobool, label %land.lhs.true, label %if.else, !dbg !31

land.lhs.true:                                    ; preds = %entry
  %1 = load i8*, i8** %realm.addr, align 8, !dbg !32
  %tobool1 = icmp ne i8* %1, null, !dbg !32
  br i1 %tobool1, label %if.then, label %if.else, !dbg !34

if.then:                                          ; preds = %land.lhs.true
  %2 = load i8*, i8** %service.addr, align 8, !dbg !35
  %3 = load i8*, i8** %host.addr, align 8, !dbg !36
  %4 = load i8*, i8** %realm.addr, align 8, !dbg !37
  %call = call i8* (i8*, ...) @curl_maprintf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), i8* %2, i8* %3, i8* %4), !dbg !38
  store i8* %call, i8** %spn, align 8, !dbg !39
  br label %if.end10, !dbg !40

if.else:                                          ; preds = %land.lhs.true, %entry
  %5 = load i8*, i8** %host.addr, align 8, !dbg !41
  %tobool2 = icmp ne i8* %5, null, !dbg !41
  br i1 %tobool2, label %if.then3, label %if.else5, !dbg !43

if.then3:                                         ; preds = %if.else
  %6 = load i8*, i8** %service.addr, align 8, !dbg !44
  %7 = load i8*, i8** %host.addr, align 8, !dbg !45
  %call4 = call i8* (i8*, ...) @curl_maprintf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i8* %6, i8* %7), !dbg !46
  store i8* %call4, i8** %spn, align 8, !dbg !47
  br label %if.end9, !dbg !48

if.else5:                                         ; preds = %if.else
  %8 = load i8*, i8** %realm.addr, align 8, !dbg !49
  %tobool6 = icmp ne i8* %8, null, !dbg !49
  br i1 %tobool6, label %if.then7, label %if.end, !dbg !51

if.then7:                                         ; preds = %if.else5
  %9 = load i8*, i8** %service.addr, align 8, !dbg !52
  %10 = load i8*, i8** %realm.addr, align 8, !dbg !53
  %call8 = call i8* (i8*, ...) @curl_maprintf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i8* %9, i8* %10), !dbg !54
  store i8* %call8, i8** %spn, align 8, !dbg !55
  br label %if.end, !dbg !56

if.end:                                           ; preds = %if.then7, %if.else5
  br label %if.end9

if.end9:                                          ; preds = %if.end, %if.then3
  br label %if.end10

if.end10:                                         ; preds = %if.end9, %if.then
  %11 = load i8*, i8** %spn, align 8, !dbg !57
  ret i8* %11, !dbg !58
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i8* @curl_maprintf(i8*, ...) #2

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_auth_user_contains_domain(i8* %user) #0 !dbg !13 {
entry:
  %user.addr = alloca i8*, align 8
  %valid = alloca i8, align 1
  %p = alloca i8*, align 8
  store i8* %user, i8** %user.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %user.addr, metadata !59, metadata !21), !dbg !60
  call void @llvm.dbg.declare(metadata i8* %valid, metadata !61, metadata !21), !dbg !62
  store i8 0, i8* %valid, align 1, !dbg !62
  %0 = load i8*, i8** %user.addr, align 8, !dbg !63
  %tobool = icmp ne i8* %0, null, !dbg !63
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !65

land.lhs.true:                                    ; preds = %entry
  %1 = load i8*, i8** %user.addr, align 8, !dbg !66
  %2 = load i8, i8* %1, align 1, !dbg !68
  %conv = sext i8 %2 to i32, !dbg !68
  %tobool1 = icmp ne i32 %conv, 0, !dbg !68
  br i1 %tobool1, label %if.then, label %if.end, !dbg !69

if.then:                                          ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i8** %p, metadata !70, metadata !21), !dbg !72
  %3 = load i8*, i8** %user.addr, align 8, !dbg !73
  %call = call i8* @strpbrk(i8* %3, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0)) #4, !dbg !74
  store i8* %call, i8** %p, align 8, !dbg !72
  %4 = load i8*, i8** %p, align 8, !dbg !75
  %cmp = icmp ne i8* %4, null, !dbg !76
  br i1 %cmp, label %land.lhs.true3, label %land.end, !dbg !77

land.lhs.true3:                                   ; preds = %if.then
  %5 = load i8*, i8** %p, align 8, !dbg !78
  %6 = load i8*, i8** %user.addr, align 8, !dbg !80
  %cmp4 = icmp ugt i8* %5, %6, !dbg !81
  br i1 %cmp4, label %land.rhs, label %land.end, !dbg !82

land.rhs:                                         ; preds = %land.lhs.true3
  %7 = load i8*, i8** %p, align 8, !dbg !83
  %8 = load i8*, i8** %user.addr, align 8, !dbg !85
  %9 = load i8*, i8** %user.addr, align 8, !dbg !86
  %call6 = call i64 @strlen(i8* %9) #4, !dbg !87
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 %call6, !dbg !88
  %add.ptr7 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !89
  %cmp8 = icmp ult i8* %7, %add.ptr7, !dbg !90
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true3, %if.then
  %10 = phi i1 [ false, %land.lhs.true3 ], [ false, %if.then ], [ %cmp8, %land.rhs ]
  %cond = select i1 %10, i32 1, i32 0, !dbg !91
  %tobool10 = icmp ne i32 %cond, 0, !dbg !93
  %frombool = zext i1 %tobool10 to i8, !dbg !94
  store i8 %frombool, i8* %valid, align 1, !dbg !94
  br label %if.end, !dbg !95

if.end:                                           ; preds = %land.end, %land.lhs.true, %entry
  %11 = load i8, i8* %valid, align 1, !dbg !96
  %tobool11 = trunc i8 %11 to i1, !dbg !96
  ret i1 %tobool11, !dbg !97
}

; Function Attrs: nounwind readonly
declare i8* @strpbrk(i8*, i8*) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!17, !18}
!llvm.ident = !{!19}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/vauth/vauth.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !13}
!6 = distinct !DISubprogram(name: "Curl_auth_build_spn", scope: !1, file: !1, line: 53, type: !7, isLocal: false, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !11, !11, !11}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !10)
!13 = distinct !DISubprogram(name: "Curl_auth_user_contains_domain", scope: !1, file: !1, line: 128, type: !14, isLocal: false, isDefinition: true, scopeLine: 129, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!14 = !DISubroutineType(types: !15)
!15 = !{!16, !11}
!16 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!17 = !{i32 2, !"Dwarf Version", i32 4}
!18 = !{i32 2, !"Debug Info Version", i32 3}
!19 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!20 = !DILocalVariable(name: "service", arg: 1, scope: !6, file: !1, line: 53, type: !11)
!21 = !DIExpression()
!22 = !DILocation(line: 53, column: 39, scope: !6)
!23 = !DILocalVariable(name: "host", arg: 2, scope: !6, file: !1, line: 53, type: !11)
!24 = !DILocation(line: 53, column: 60, scope: !6)
!25 = !DILocalVariable(name: "realm", arg: 3, scope: !6, file: !1, line: 54, type: !11)
!26 = !DILocation(line: 54, column: 39, scope: !6)
!27 = !DILocalVariable(name: "spn", scope: !6, file: !1, line: 56, type: !9)
!28 = !DILocation(line: 56, column: 9, scope: !6)
!29 = !DILocation(line: 59, column: 6, scope: !30)
!30 = distinct !DILexicalBlock(scope: !6, file: !1, line: 59, column: 6)
!31 = !DILocation(line: 59, column: 11, scope: !30)
!32 = !DILocation(line: 59, column: 14, scope: !33)
!33 = !DILexicalBlockFile(scope: !30, file: !1, discriminator: 1)
!34 = !DILocation(line: 59, column: 6, scope: !33)
!35 = !DILocation(line: 60, column: 31, scope: !30)
!36 = !DILocation(line: 60, column: 40, scope: !30)
!37 = !DILocation(line: 60, column: 46, scope: !30)
!38 = !DILocation(line: 60, column: 11, scope: !30)
!39 = !DILocation(line: 60, column: 9, scope: !30)
!40 = !DILocation(line: 60, column: 5, scope: !30)
!41 = !DILocation(line: 61, column: 11, scope: !42)
!42 = distinct !DILexicalBlock(scope: !30, file: !1, line: 61, column: 11)
!43 = !DILocation(line: 61, column: 11, scope: !30)
!44 = !DILocation(line: 62, column: 28, scope: !42)
!45 = !DILocation(line: 62, column: 37, scope: !42)
!46 = !DILocation(line: 62, column: 11, scope: !42)
!47 = !DILocation(line: 62, column: 9, scope: !42)
!48 = !DILocation(line: 62, column: 5, scope: !42)
!49 = !DILocation(line: 63, column: 11, scope: !50)
!50 = distinct !DILexicalBlock(scope: !42, file: !1, line: 63, column: 11)
!51 = !DILocation(line: 63, column: 11, scope: !42)
!52 = !DILocation(line: 64, column: 28, scope: !50)
!53 = !DILocation(line: 64, column: 37, scope: !50)
!54 = !DILocation(line: 64, column: 11, scope: !50)
!55 = !DILocation(line: 64, column: 9, scope: !50)
!56 = !DILocation(line: 64, column: 5, scope: !50)
!57 = !DILocation(line: 67, column: 10, scope: !6)
!58 = !DILocation(line: 67, column: 3, scope: !6)
!59 = !DILocalVariable(name: "user", arg: 1, scope: !13, file: !1, line: 128, type: !11)
!60 = !DILocation(line: 128, column: 49, scope: !13)
!61 = !DILocalVariable(name: "valid", scope: !13, file: !1, line: 130, type: !16)
!62 = !DILocation(line: 130, column: 8, scope: !13)
!63 = !DILocation(line: 132, column: 6, scope: !64)
!64 = distinct !DILexicalBlock(scope: !13, file: !1, line: 132, column: 6)
!65 = !DILocation(line: 132, column: 11, scope: !64)
!66 = !DILocation(line: 132, column: 15, scope: !67)
!67 = !DILexicalBlockFile(scope: !64, file: !1, discriminator: 1)
!68 = !DILocation(line: 132, column: 14, scope: !67)
!69 = !DILocation(line: 132, column: 6, scope: !67)
!70 = !DILocalVariable(name: "p", scope: !71, file: !1, line: 134, type: !9)
!71 = distinct !DILexicalBlock(scope: !64, file: !1, line: 132, column: 21)
!72 = !DILocation(line: 134, column: 11, scope: !71)
!73 = !DILocation(line: 134, column: 23, scope: !71)
!74 = !DILocation(line: 134, column: 15, scope: !71)
!75 = !DILocation(line: 136, column: 14, scope: !71)
!76 = !DILocation(line: 136, column: 16, scope: !71)
!77 = !DILocation(line: 136, column: 24, scope: !71)
!78 = !DILocation(line: 136, column: 27, scope: !79)
!79 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 1)
!80 = !DILocation(line: 136, column: 31, scope: !79)
!81 = !DILocation(line: 136, column: 29, scope: !79)
!82 = !DILocation(line: 136, column: 36, scope: !79)
!83 = !DILocation(line: 136, column: 39, scope: !84)
!84 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 2)
!85 = !DILocation(line: 136, column: 43, scope: !84)
!86 = !DILocation(line: 136, column: 57, scope: !84)
!87 = !DILocation(line: 136, column: 50, scope: !84)
!88 = !DILocation(line: 136, column: 48, scope: !84)
!89 = !DILocation(line: 136, column: 63, scope: !84)
!90 = !DILocation(line: 136, column: 41, scope: !84)
!91 = !DILocation(line: 136, column: 14, scope: !92)
!92 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 3)
!93 = !DILocation(line: 136, column: 13, scope: !92)
!94 = !DILocation(line: 136, column: 11, scope: !92)
!95 = !DILocation(line: 138, column: 3, scope: !71)
!96 = !DILocation(line: 146, column: 10, scope: !13)
!97 = !DILocation(line: 146, column: 3, scope: !13)
